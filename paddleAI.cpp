#include "Paddle.h"
#include "Game.h"
#include "Ball.h"
#include "PaddleAI.h"

PaddleAI::PaddleAI(Game* game, Ball* ball, float height, float width, float speed)
: Paddle{game, height, width}, ball{ball}, m_x{game->getWindowWidth()/2.0f}, m_speed {speed}
{
    m_y = game->getWindowHeight() / 2.0f;
}

/**
 * @brief Updates the PaddleAI's position based on the given deltaTime.
 * 
 * The paddle moves up and down based on its current direction and speed.
 * If the paddle reaches the top or bottom of the screen, it changes direction.
 * 
 * @param deltaTime The time elapsed since the last update.
 */
void PaddleAI::update(float deltaTime)
{
    m_y += m_direction * m_speed * deltaTime;

    // Prevent movement off screen
    if (m_y < m_height / 2.0f + 15)
    {
        m_y = m_height / 2.0f + 15;
        m_direction *= -1;
    }
    else if (m_y > (m_game->getWindowHeight() - m_height / 2.0f - 15))
    {
        m_y = m_game->getWindowHeight() - m_height / 2.0f - 15;
        m_direction *= -1;
    }
}
