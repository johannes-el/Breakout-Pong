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

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_Rect wallTop{
        0, // Top left x
        0, // Top left y
        m_windowWidth, // Width
        15 // Height
    };
    SDL_Rect wallBottom{0, m_windowHeight - 15, m_windowWidth, 15};
    // SDL_Rect wallRight{m_windowWidth - 15, 0, 15, m_windowHeight};
    SDL_Rect ballRect
    {
        static_cast<int>(m_ball->getX() - 15 / 2),
        static_cast<int>(m_ball->getY() - 15 / 2),
        15,
        15
    };
    SDL_Rect paddleRect
    {
        static_cast<int>(m_paddle->getX()),
        static_cast<int>(m_paddle->getY() - 50),
        15,
        100
    };
    SDL_Rect paddleAIRect
    {
        static_cast<int>(getWindowWidth() - 15),
        static_cast<int>(m_paddleAI->getY() - 50),
        15,
        100
    };
    SDL_RenderFillRect(m_renderer, &wallTop);
    SDL_RenderFillRect(m_renderer, &wallBottom);
    // SDL_RenderFillRect(m_renderer, &wallRight);
    SDL_RenderFillRect(m_renderer, &ballRect);
    SDL_RenderFillRect(m_renderer, &paddleRect);
    SDL_RenderFillRect(m_renderer, &paddleAIRect);
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
    m_ticksCount = SDL_GetTicks();
    // Limit maximum delta time
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    if (m_paddle->getDirection() != 0)
    {
        m_paddle->update(deltaTime);
    }

    m_paddleAI->setDirection();

    m_paddleAI->update(deltaTime);

    m_ball->update(deltaTime);

    m_ball->collideWithWall();

    m_ball->collideWithPaddle();

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