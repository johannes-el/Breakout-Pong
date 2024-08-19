#include "Paddle.h"
#include "Game.h"

Paddle::Paddle(Game* game) : m_x {100}, m_y {game->getWindowHeight()/2.0f}, game {game} {}

void Paddle::resetDirection(){ m_direction = 0; }

void Paddle::setDirection(int dir) { m_direction += dir; }

void Paddle::update(float deltaTime)
{
    m_y += m_direction * 400.0f * deltaTime;
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