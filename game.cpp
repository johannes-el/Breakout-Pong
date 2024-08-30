#include "Game.h"
#include "Paddle.h"
#include "PaddleAI.h"
#include "Ball.h"

/**
 * Initializes the game.
 * 
 * This function initializes the SDL library, creates a window, and a renderer for the game.
 * It also retrieves the window size and generates the tiles for the game.
 * 
 * @return True if the initialization is successful, false otherwise.
 */
bool Game::initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow(
        "Breakout Pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024,
        768,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
    );

    if (!m_window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!m_renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
    std::cout << "Window size: " << m_windowWidth << "x" << m_windowHeight << std::endl;
    TileFactory tileFactory(this);
    m_tiles = tileFactory.generateTiles();

    return true;
}


/**
 * Process the user input for the game.
 * This function handles events such as quitting the game and keyboard input.
 */
void Game::processInput()
{
    SDL_Event event;
    m_paddle->resetDirection();

    // Go through all events in the event queue
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_isRunning = false;
            break;
        }
    }

    // Get the state of the keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);

    m_paddle->resetDirection();

    bool currentPauseState = state[SDL_SCANCODE_P];
    if (currentPauseState && !m_pausedPrevious)
    {
        m_paused = !m_paused;
    }
    m_pausedPrevious = currentPauseState;

    if (state[SDL_SCANCODE_UP])
    {
        m_paddle->setDirection(-2);
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        m_paddle->setDirection(2);
    }
}

/**
 * Renders the game output to the screen.
 * This function clears the renderer, sets the draw color, and renders various game elements such as walls, ball, paddles, and tiles.
 */
void Game::generateOutput()
{
    SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_Rect wallTop{
        0, // Top left x
        0, // Top left y
        m_windowWidth, // Width
        15 // Height
    };
    SDL_Rect wallBottom{0, m_windowHeight - 15, m_windowWidth, 15};
    int ballRadius = m_ball->getWidth() / 2;
    int ballCenterX = static_cast<int>(m_ball->getX() + ballRadius);
    int ballCenterY = static_cast<int>(m_ball->getY() + ballRadius);
    m_ball->drawBall(m_renderer, m_ball->getX(), m_ball->getY(), m_ball->getWidth());
    SDL_Rect paddleRect
    {
        static_cast<int>(m_paddle->getX()),
        static_cast<int>(m_paddle->getY() - m_paddle->getHeight() / 2.0f),
        static_cast<int>(m_paddle->getWidth()),
        static_cast<int>(m_paddle->getHeight())
    };
    SDL_Rect paddleAIRect
    {
        static_cast<int>(m_paddleAI->getX()),
        static_cast<int>(m_paddleAI->getY() - m_paddleAI->getHeight() / 2.0f),
        static_cast<int>(m_paddleAI->getWidth()),
        static_cast<int>(m_paddleAI->getHeight())
    };
    // Render all the tiles in the vector
    for (auto& tile : m_tiles)
    {
        SDL_Rect tileRect
        {
            static_cast<int>(tile.getX()),
            static_cast<int>(tile.getY()),
            static_cast<int>(tile.getWidth()),
            static_cast<int>(tile.getHeight())
        };
        switch (tile.getColor())
        {
            case 0:
                SDL_SetRenderDrawColor(m_renderer, 240, 240, 240, 255);
                break;
            case 1:
                SDL_SetRenderDrawColor(m_renderer, 220, 220, 220, 220);
                break;
            case 2:
                SDL_SetRenderDrawColor(m_renderer, 200, 200, 200, 255);
                break;
            case 3:
                SDL_SetRenderDrawColor(m_renderer, 180, 180, 180, 255);
                break;
            case 4:
                SDL_SetRenderDrawColor(m_renderer, 160, 160, 160, 255);
                break;
            case 5:
                SDL_SetRenderDrawColor(m_renderer, 140, 140, 140, 255);
                break;
        }
        SDL_RenderFillRect(m_renderer, &tileRect);
    }
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_renderer, &wallTop);
    SDL_RenderFillRect(m_renderer, &wallBottom);
    SDL_RenderFillRect(m_renderer, &paddleRect);
    if (!(m_ball->getSpeed().x < 0 && m_ball->getX() <= m_paddleAI->getX()+100 && m_ball->getX() >= m_paddleAI->getX()-100
        && m_ball->getY() <= m_paddleAI->getY()+100 && m_ball->getY() >= m_paddleAI->getY()-100
        && m_ball->getTileBroken()))
    {
        SDL_RenderFillRect(m_renderer, &paddleAIRect); // Hide paddleAI when ball is bouncing off tiles
    }
    SDL_RenderPresent(m_renderer);
}

/**
 * Updates the game state.
 * 
 * This function is responsible for updating the game state, including the positions and behaviors of the paddle, ball, and tiles.
 * It also handles collision detection between the ball and the walls, paddle, and tiles.
 * The game state is updated based on the elapsed time since the last update.
 * 
 * @note This function does not update the game state if the game is paused.
 * 
 * @note The maximum delta time is limited to 0.05 seconds to prevent large time gaps between updates.
 * 
 * @note If the ball goes off the screen, the game is ended.
 */
void Game::updateGame()
{
    SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);

    if (!m_paused) // Only update the game if it is not paused
    {
        while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksCount + 16))
        {
            ;
        }
        float deltaTime = (SDL_GetTicks() - m_ticksCount) / 1000.0f;

        // Limit maximum delta time
        if (deltaTime > 0.05f)
        {
            deltaTime = 0.05f;
        }

        m_ticksCount = SDL_GetTicks();

        if (m_paddle->getDirection() != 0)
        {
            m_paddle->update(deltaTime);
        }
        m_paddleAI->update(deltaTime);
        m_ball->update(deltaTime);
        m_ball->collideWithWall();
        m_ball->collideWithPaddle();
        m_ball->collideWithTile(m_tiles);

        if (m_ball->ballOffScreen())
        {
            m_isRunning = false;
        }
    }
}

/**
 * @brief Shuts down the game by destroying the window, renderer, and quitting SDL.
 */
void Game::shutdown()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

/**
 * Runs the game loop until the game is no longer running.
 * The game loop consists of three main steps: processing input, updating the game state, and generating output.
 */
void Game::runLoop()
{
    while (m_isRunning)
    {
        processInput();
        updateGame();
        generateOutput();
    }
}