#include "Game.h"
#include "Paddle.h"
#include "PaddleAI.h"
#include "Ball.h"

bool Game::initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow(
        "Pong",
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

    TileFactory tileFactory(this);
    tiles = tileFactory.generateTiles();

    return true;
}


void Game::processInput()
{
    SDL_Event event;
    m_paddle->resetDirection();

    // Goes through all events in the event queue
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_isRunning = false;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
                // m_paddleAI->handleWindowResize();
            }
            break;
        }
    }
    // get the state of the keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);
    m_paddle->resetDirection();
    if (state[SDL_SCANCODE_UP])
    {
        m_paddle->setDirection(-2);
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        m_paddle->setDirection(2);
    }
}

void Game::generateOutput()
{
    // Query the window size
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
    SDL_Rect ballRect
    {
        static_cast<int>(m_ball->getX()),
        static_cast<int>(m_ball->getY()),
        15,
        15
    };
    SDL_Rect paddleRect
    {
        static_cast<int>(m_paddle->getX()),
        static_cast<int>(m_paddle->getY() - m_paddle->getHeight() / 2.0f),
        15,
        100
    };
    SDL_Rect paddleAIRect
    {
        static_cast<int>(m_paddleAI->getX()),
        static_cast<int>(m_paddleAI->getY() - m_paddleAI->getHeight() / 2.0f),
        15,
        100
    };
    // Render all the tiles in the vector
    for (auto& tile : tiles)
    {
        SDL_Rect tileRect
        {
            static_cast<int>(tile.getX()),
            static_cast<int>(tile.getY()),
            static_cast<int>(tile.getWidth()),
            static_cast<int>(tile.getHeight())
        };
        SDL_RenderFillRect(m_renderer, &tileRect);
    }
    SDL_RenderFillRect(m_renderer, &wallTop);
    SDL_RenderFillRect(m_renderer, &wallBottom);
    SDL_RenderFillRect(m_renderer, &ballRect);
    SDL_RenderFillRect(m_renderer, &paddleRect);
    if (!(m_ball->getSpeed().x < 0 && m_ball->getX() <= m_paddleAI->getX()+100 && m_ball->getX() >= m_paddleAI->getX()-100
        && m_ball->getY() <= m_paddleAI->getY()+50 && m_ball->getY() >= m_paddleAI->getY()-50
        && m_ball->getTileBroken()))
    {
        std::cout << "State of m_tileBroken: " << m_ball->getTileBroken() << std::endl;
        SDL_RenderFillRect(m_renderer, &paddleAIRect); // Hide paddleAI when ball is bouncing off tiles
    }
    SDL_RenderPresent(m_renderer);
}

void Game::updateGame()
{
    // Query the window size
    SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);

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

    m_paddleAI->setDirection();

    m_paddleAI->update(deltaTime);

    m_ball->update(deltaTime);

    m_ball->collideWithWall();

    m_ball->collideWithPaddle();

    m_ball->collideWithTile(tiles);

    if (m_ball->ballOffScreen())
    {
        m_isRunning = false;
    }
}

void Game::shutdown()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void Game::runLoop()
{
    while (m_isRunning)
    {
        processInput();
        updateGame();
        generateOutput();
    }
}