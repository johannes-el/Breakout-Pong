#include "Paddle.h"
#include "Game.h"

Paddle::Paddle(Game* game, float height, float width)
: m_x {125}, m_y {game->getWindowHeight()/2.0f}, m_height{height}, m_width {width}, m_game {game} {}

void Paddle::resetDirection(){ m_direction = 0; }

void Paddle::setDirection(int dir) { m_direction += dir; }

/**
 * Updates the position of the paddle based on the direction given by user input and deltaTime.
 * 
 * @param deltaTime The time elapsed since the last update.
 */
void Paddle::update(float deltaTime)
{
    m_y += m_direction * 400.0f * deltaTime;
    
    // Prevent movement off screen
    if (m_y < m_height / 2.0f + 15)
    {
        m_y = m_height / 2.0f + 15;
    }
    else if (m_y > (m_game->getWindowHeight() - m_height / 2.0f - 15))
    {
        m_y = m_game->getWindowHeight() - m_height / 2.0f - 15;
    }
}