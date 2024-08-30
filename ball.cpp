#include "Ball.h"
#include "Game.h"
#include "Paddle.h"
#include "PaddleAI.h"
#include "Tile.h"
#include <random>

/**
 * @brief Constructs a Ball object with the specified parameters. Randomizes the starting speed of the ball.
 * 
 * @param width The width of the ball.
 * @param speed The speed of the ball.
 * @param game Pointer to the Game object.
 * @param paddle Pointer to the Paddle object.
 * @param paddleAI Pointer to the PaddleAI object.
 */
Ball::Ball(float width, Ball::speed speed, Game* game)
: m_tileBroken {false}, m_width {width}, m_game {game}, m_x {game->getWindowWidth()/2.5f}, m_y {game->getWindowHeight()/2.0f}
{
    // Random coin flip to initialize direction
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    int coinFlip = dis(gen);
    if (coinFlip == 0)
    {
        m_speed = {-speed.x, speed.y};
    }
    else
    {
        m_speed = {-speed.x, -speed.y};
    }
    // Random value between 0 and 50 to initialize speed
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

/**
 * @brief Draws a ball on the screen.
 * 
 * This function is responsible for drawing a ball on the screen using the provided SDL_Renderer object.
 * 
 * @param renderer The SDL_Renderer object used for rendering.
 * @param centerX The x-coordinate of the center of the ball.
 * @param centerY The y-coordinate of the center of the ball.
 * @param radius The radius of the ball.
 */
void Ball::drawBall(SDL_Renderer* renderer, int centerX, int centerY, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

/**
 * @brief Updates the position of the ball based on the given deltaTime.
 * 
 * @param deltaTime The time elapsed since the last update.
 */
void Ball::update(float deltaTime)
{
    m_x += m_speed.x * deltaTime;
    m_y += m_speed.y * deltaTime;
}

/**
 * @brief Handles the collision of the ball with the walls.
 * 
 * If the ball's y-coordinate is less than or equal to the height of the wall and the vertical speed is negative,
 * the ball's vertical speed is reversed to simulate bouncing off the top wall.
 * If the ball's y-coordinate is greater than or equal to the window height minus the ball's width plus the height of the wall
 * and the vertical speed is positive, the ball's vertical speed is reversed to simulate bouncing off the bottom wall.
 */
void Ball::collideWithWall()
{
    if (m_y <= 15 && m_speed.y < 0) // 15 is the height of the wall
    {
        m_speed.y *= -1;
    }
    else if (m_y >= m_game->getWindowHeight() - (m_width + 15) && m_speed.y > 0)
    {
        m_speed.y *= -1;
    }
}

/**
 * Detects collision between the ball and the paddles.
 * 
 * @return true if collision is detected, false otherwise.
 */
bool Ball::detectCollisionWithPaddle(const Paddle* paddle, const PaddleAI* paddleAI)
{
    if (m_x <= paddle->getX() + paddle->getWidth() && m_x >= paddle->getX() && m_y >= paddle->getY() - paddle->getHeight()/2.0f && m_y <= paddle->getY() + paddle->getHeight()/2.0f && m_speed.x < 0)
    {
        m_tileBroken = false;
        return true;
    }
    if (m_x + m_width >= paddleAI->getX() && m_x + m_width <= paddleAI->getX() + paddleAI->getWidth() && m_y >= paddleAI->getY() - paddleAI->getHeight()/2.0f && m_y <= paddleAI->getY() + paddleAI->getHeight()/2.0f && m_speed.x > 0)
    {
        m_tileBroken = false;
        return true;
    }

    return false;
}

/**
 * @brief Checks if the ball collides with the paddle and updates its speed accordingly.
 * 
 * This function checks if the ball collides with the paddle by calling the detectCollisionWithPaddle() function.
 * If a collision is detected, the ball's horizontal speed is reversed.
 */
void Ball::collideWithPaddle()
{
    if (detectCollisionWithPaddle(m_game->getPaddle(), m_game->getPaddleAI()))
    {
        m_speed.x *= -1;
    }
}

/**
 * @brief Handles collision between the ball and tiles.
 * 
 * This function checks for collision between the ball and each tile in the provided vector.
 * If a collision is detected, the ball's speed is updated accordingly and the tile is removed from the vector.
 * 
 * @param tiles The vector of tiles to check for collision with the ball.
 */
void Ball::collideWithTile(std::vector<Tile>& tiles)
{
    for (auto i = tiles.begin(); i != tiles.end();)
    {
        // Calculate the bounding box of the ball
        std::pair<float, float> ballUpperLeft = {m_x, m_y};
        std::pair<float, float> ballUpperRight = {m_x + m_width, m_y};
        std::pair<float, float> ballLowerLeft = {m_x, m_y + m_width};
        std::pair<float, float> ballLowerRight = {m_x + m_width, m_y + m_width};

        // Calculate the bounding box of the tile
        std::pair<float, float> tileUpperLeft = {i->getX(), i->getY()};
        std::pair<float, float> tileUpperRight = {i->getX() + i->getWidth(), i->getY()};
        std::pair<float, float> tileLowerLeft = {i->getX(), i->getY() + i->getHeight()};
        std::pair<float, float> tileLowerRight = {i->getX() + i->getWidth(), i->getY() + i->getHeight()};

        // Collision from left side
        if (ballUpperRight.first >= tileUpperLeft.first && ballUpperRight.first <= tileUpperRight.first && ballUpperRight.second >= tileUpperLeft.second
            && ballLowerRight.second <= tileLowerLeft.second)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(10, 20);
            m_speed.x *= -1;
            if (m_speed.x < 0)
            {
                m_speed.x -= dis(gen);
            }
            else
            {
                m_speed.x += dis(gen);
            }
            if (m_speed.y < 0)
            {
                m_speed.y -= dis(gen);
            }
            else
            {
                m_speed.y += dis(gen);
            }
            m_tileBroken = true;
            i = tiles.erase(i);
        }

        // Collision from right side
        else if (ballUpperLeft.first <= tileUpperRight.first && ballUpperLeft.first >= tileUpperLeft.first && ballUpperLeft.second >= tileUpperRight.second
            && ballLowerLeft.second <= tileLowerRight.second)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(10, 20);
            m_speed.x *= -1;
            if (m_speed.x < 0)
            {
                m_speed.x -= dis(gen);
            }
            else
            {
                m_speed.x += dis(gen);
            }
            if (m_speed.y < 0)
            {
                m_speed.y -= dis(gen);
            }
            else
            {
                m_speed.y += dis(gen);
            }
            m_tileBroken = true;
            i = tiles.erase(i);
        }

        // Collision from top
        else if (ballLowerLeft.second >= tileUpperLeft.second && ballLowerLeft.second <= tileLowerLeft.second && ballLowerLeft.first >= tileUpperLeft.first
            && ballLowerRight.first <= tileUpperRight.first)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(10, 20);
            m_speed.y *= -1;
            if (m_speed.x < 0)
            {
                m_speed.x -= dis(gen);
            }
            else
            {
                m_speed.x += dis(gen);
            }
            if (m_speed.y < 0)
            {
                m_speed.y -= dis(gen);
            }
            else
            {
                m_speed.y += dis(gen);
            }
            m_tileBroken = true;
            i = tiles.erase(i);
        }

        // Collision from bottom
        else if (ballUpperLeft.second <= tileLowerLeft.second && ballUpperLeft.second >= tileUpperLeft.second && ballUpperLeft.first >= tileLowerLeft.first
            && ballUpperRight.first <= tileLowerRight.first)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(10, 20);
            m_speed.y *= -1;
            if (m_speed.x < 0)
            {
                m_speed.x -= dis(gen);
            }
            else
            {
                m_speed.x += dis(gen);
            }
            if (m_speed.y < 0)
            {
                m_speed.y -= dis(gen);
            }
            else
            {
                m_speed.y += dis(gen);
            }
            m_tileBroken = true;
            i = tiles.erase(i);
        }

        else
        {
            i++;
        }
    }
}

/**
 * Checks if the ball is off the screen.
 * 
 * @return true if the ball is off the screen, false otherwise.
 */
bool Ball::ballOffScreen()
{
    if (m_x <= 0 || m_x >= m_game->getWindowWidth())
    {
        return true;
    }
    return false;
}