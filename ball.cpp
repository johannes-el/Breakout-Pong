#include "Ball.h"
#include "Game.h"
#include "Paddle.h"
#include "PaddleAI.h"

void Ball::update(float deltaTime)
{
    m_x += m_speed.x * deltaTime;
    m_y += m_speed.y * deltaTime;
}

void Ball::collideWithWall()
{
    if (m_y <= 15 && m_speed.y < 0)
    {
        m_speed.y *= -1;
    }
    else if (m_y >= m_game->getWindowHeight() - 15 && m_speed.y > 0)
    {
        m_speed.y *= -1;
    }
    else if (m_x >= m_game->getWindowWidth() - 15 && m_speed.x > 0)
    {
        m_speed.x *= -1;
    }
}

void Ball::collideWithPaddle()
{
    float diffPaddle = m_y - m_paddle->getY();
    float diffPaddleAI = m_y - m_paddleAI->getY();
    if (
        (diffPaddle <= m_paddle->getHeight() / 2.0f && diffPaddle >= -m_paddle->getHeight() / 2.0f && m_x <= 25 && m_speed.x < 0)
        || (diffPaddleAI <= m_paddleAI->getHeight() / 2.0f && diffPaddleAI >= -m_paddleAI->getHeight() / 2.0f && m_x >= m_game->getWindowWidth() - 25 && m_speed.x > 0)
    )
    {
        m_speed.x *= -1;
    }
}

bool Ball::ballOffScreen()
{
    if (m_x <= 0)
    {
        return true;
    }
    return false;
}