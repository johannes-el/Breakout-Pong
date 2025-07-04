#include "Game.h"
#include "Paddle.h"
#include "PaddleAI.h"
#include "Ball.h"
#include "Logger.h"
#include "Menu.h"

#include <format>
#include <SDL_ttf.h>

/**
 * Initializes the game.
 * 
 * This function initializes the SDL library, creates a window, and a renderer for the game.
 * It also retrieves the window size and generates the tiles for the game.
 * 
 * @return True if the initialization is successful, false otherwise.
 */


constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;

constexpr int PaddleAICollisionRange = 100;

static const SDL_Color tileColors[] = {
    {240, 240, 240, 255},
    {220, 220, 220, 220},
    {200, 200, 200, 255},
    {180, 180, 180, 255},
    {160, 160, 160, 255},
    {140, 140, 140, 255}
};

bool Game::initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow(
        "Breakout-Pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
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

    if (TTF_Init() == -1) {
        Logger::Debug(std::format("TTF_Init Error: {}", TTF_GetError()));
        return false;
    }


    SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
    if (m_debugMode)
    {
        Logger::Debug(std::format("Window size: {}x{}", m_windowWidth, m_windowHeight));
    }
    TileFactory tileFactory(this);
    m_tiles = tileFactory.generateTiles();

    Menu::initMenu(SCREEN_WIDTH, SCREEN_HEIGHT);

    return true;
}


void Game::drawRunning()
{
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

    SDL_Rect wallTop{0, 0, m_windowWidth, 15};
    SDL_Rect wallBottom{0, m_windowHeight - 15, m_windowWidth, 15};

    int ballRadius = m_ball->getWidth() / 2;
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

    for (auto& tile : m_tiles)
    {
        SDL_Rect tileRect
        {
            static_cast<int>(tile.getX()),
            static_cast<int>(tile.getY()),
            static_cast<int>(tile.getWidth()),
            static_cast<int>(tile.getHeight())
        };

        int colorIndex = tile.getColor();
        if (colorIndex >= 0 && colorIndex < static_cast<int>(std::size(tileColors)))
        {
            SDL_Color c = tileColors[colorIndex];
            SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
        }

        SDL_RenderFillRect(m_renderer, &tileRect);
    }

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_renderer, &wallTop);
    SDL_RenderFillRect(m_renderer, &wallBottom);
    SDL_RenderFillRect(m_renderer, &paddleRect);

    if (!(m_ball->getSpeed().x < 0 && m_ball->getX() <= m_paddleAI->getX() + PaddleAICollisionRange
        && m_ball->getX() >= m_paddleAI->getX() - PaddleAICollisionRange
        && m_ball->getY() <= m_paddleAI->getY() + PaddleAICollisionRange
        && m_ball->getY() >= m_paddleAI->getY() - PaddleAICollisionRange
        && m_ball->getTileBroken()))
    {
        SDL_RenderFillRect(m_renderer, &paddleAIRect);
    }
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
    const Uint8* state = SDL_GetKeyboardState(nullptr);

    m_paddle->resetDirection();

    bool currentPauseState = state[SDL_SCANCODE_P];
    if (currentPauseState && !m_pausedPrevious)
    {
        m_paused = !m_paused;
    }
    m_pausedPrevious = currentPauseState;

    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])
    {
        m_paddle->setDirection(-2);
    }
    if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])
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

    switch(m_state)
    {
        case GameState::MENU:
            Menu::drawStartMenu(m_renderer);
            break;

        case GameState::RUNNING:
            drawRunning();
            break;
        
        case GameState::VICTORY:
        case GameState::GAME_OVER:
            Menu::drawEndMenu(m_renderer, m_state);
            break;
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
    if (m_state == GameState::MENU)
    {
        Menu::updateStartMenu(m_state);

        const Uint8* state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_RETURN])
        {
            m_state = GameState::RUNNING;
        }
    }

    if (m_state == GameState::GAME_OVER || m_state == GameState::VICTORY)
    {
        Menu::updateEndMenu(m_state);
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_RETURN])
        {
            m_state = GameState::QUIT;
        }
    }

    if (m_state == GameState::QUIT)
    {
        m_isRunning = false;
    }

    if (m_state != GameState::RUNNING || m_paused) return;

    SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);

    while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksCount + 16))
    {
        ;
    }
    float deltaTime = (SDL_GetTicks() - m_ticksCount) / 1000.0f;

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

    if (m_ball->ballOffScreen()==1)
    {
        m_state = GameState::GAME_OVER;
    }
    else if (m_ball->ballOffScreen()==2)
    {
        m_state = GameState::VICTORY;
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
