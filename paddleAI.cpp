#include "Paddle.h"
#include "Game.h"
#include "Ball.h"
#include "PaddleAI.h"

PaddleAI::PaddleAI(Game* game, Ball* ball)
: Paddle{game}, ball{ball}, m_x{game->getWindowWidth()/2-100}
{
    m_y = game->getWindowHeight() / 2.0f;
}

void PaddleAI::setDirection()
{
    if (ball->getY() > m_y)
    {
        m_direction = 1;
    }
    else if (ball->getY() < m_y)
    {
        m_direction = -1;
    }
    else
    {
        m_direction = 0;
    }
}

void PaddleAI::update(float deltaTime)
{
    m_y += m_direction * 300.0f * deltaTime;
    // Prevent movement off screen
    if (m_y < m_height / 2.0f + 15)
    {
        m_y = m_height / 2.0f + 15;
    }
    else if (m_y > (game->getWindowHeight() - m_height / 2.0f - 15))
    {
        m_y = game->getWindowHeight() - m_height / 2.0f - 15;
    }
}

// void PaddleAI::handleWindowResize()
// {
//     m_x = game->getWindowWidth() - 100.0f;
//     m_y = game->getWindowHeight() / 2.0f;
// }