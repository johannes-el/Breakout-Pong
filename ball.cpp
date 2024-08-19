#include "Ball.h"
#include "Game.h"
#include "Paddle.h"
#include "PaddleAI.h"
#include "Tile.h"
#include <random>
// print the game object for debugging

Ball::Ball(const Game* game, const Paddle* paddle, const PaddleAI* paddleAI)
: m_game {game}, m_paddle {paddle}, m_paddleAI {paddleAI}, m_tileBroken {false},
m_x {game->getWindowWidth()/2.0f-50}, m_y {game->getWindowHeight()/2.0f}
{
    // Random coin flip:
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    int coinFlip = dis(gen);
    if (coinFlip == 0)
    {
        m_speed = {-350.0f, 350.0f};
    }
    else
    {
        m_speed = {-350.0f, -350.0f};
    }
    // Random value between 0 and 50:
    std::uniform_int_distribution<> dis2(0, 50);
    m_speed.x -= dis2(gen);
    if (m_speed.y < 0)
    {
        m_speed.y -= dis2(gen);
    }
    else
    {
        m_speed.y += dis2(gen);
    }
}

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
}

bool Ball::detectCollisionWithPaddle()
{
    float diffPaddle = m_y - m_paddle->getY();
    float diffPaddleAI = m_y - m_paddleAI->getY();

    if ((diffPaddle <= m_paddle->getHeight()/2.0f+15 && diffPaddle >= -m_paddle->getHeight()/2.0f-15
        && m_x >= m_paddle->getX() && m_x <= m_paddle->getX()+15 && m_speed.x < 0))
    {
        m_tileBroken = false;
        return true;
    }
    // m_paddleAI->getX()-paddleAI->getWidth()/2 <= m_x <= m_paddleAI->getX()+m_paddleAI->getWidth()/2
    else if ((diffPaddleAI <= m_paddleAI->getHeight()/2.0f+15 && diffPaddleAI >= -m_paddleAI->getHeight()/2.0f-15
            && m_x <= m_paddleAI->getX() && m_x >= m_paddleAI->getX()-15 && m_speed.x > 0))
    {
        m_tileBroken = false;
        return true;
    }

    return false;
}

void Ball::collideWithPaddle()
{
    // Ball coming from below, hits the bottom of a moving paddle
    if (detectCollisionWithPaddle() && m_speed.y < 0 && m_y > m_paddle->getY() && m_paddle->getDirection()
    || detectCollisionWithPaddle() && m_speed.y < 0 && m_y > m_paddleAI->getY() && m_paddleAI->getDirection())
    {
        m_speed.x *= -1;
        m_speed.y *= -1;
    }
    // Ball coming from above, hits the top of a moving paddle
    else if (detectCollisionWithPaddle() && m_speed.y > 0 && m_y < m_paddle->getY() && m_paddle->getDirection()
    || detectCollisionWithPaddle() && m_speed.y > 0 && m_y < m_paddleAI->getY() && m_paddleAI->getDirection())
    {
        m_speed.x *= -1;
        m_speed.y *= -1;
    }
    else if (detectCollisionWithPaddle() && m_speed.x < 0)
    {
        m_speed.x *= -1;
    }
    else if (detectCollisionWithPaddle() && m_speed.x > 0)
    {
        m_speed.x *= -1;
    }
}

void Ball::collideWithTile(std::vector<Tile>& tiles)
{
    for (auto i = tiles.begin(); i != tiles.end();)
    {
        // Calculate the bounding box of the ball
        float ballLeft = m_x;
        float ballRight = m_x;
        float ballTop = m_y;
        float ballBottom = m_y;

        // Calculate the bounding box of the tile
        float tileLeft = i->getX() - (i->getWidth() / 2.0f + 20);
        float tileRight = i->getX() + (i->getWidth() / 2.0f + 20);
        float tileTop = i->getY() - (i->getHeight() / 2.0f + 20);
        float tileBottom = i->getY() + (i->getHeight() / 2.0f + 20);

        // Check for collision
        if (ballRight >= tileLeft && ballLeft <= tileRight &&
            ballBottom >= tileTop && ballTop <= tileBottom)
        {
            i = tiles.erase(i); // erase returns the next iterator
            m_tileBroken = true;
            if (m_speed.x > 0)
            {
                m_speed.x *= -1;
                m_speed.x -= 10.0f;
                if (m_speed.y > 0)
                {
                    m_speed.y += 10.0f;
                }
                else
                {
                    m_speed.y -= 10.0f;
                }
            }
            else
            {
                m_speed.y *= -1;
                m_speed.y -= 10.0f;
                if (m_speed.x > 0)
                {
                    m_speed.x += 10.0f;
                }
                else
                {
                    m_speed.x -= 10.0f;
                }
            }
        }
        else
        {
            ++i; // only increment if not erasing
        }
    }
}

bool Ball::ballOffScreen()
{
    if (m_x <= 0 || m_x >= m_game->getWindowWidth())
    {
        return true;
    }
    return false;
}