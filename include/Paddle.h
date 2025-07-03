/**
 * @class Paddle
 * @brief Represents a paddle in the game.
 *
 * The Paddle class is responsible for managing the position, size, and movement of a paddle in the game.
 * It provides methods to get and set the paddle's position, height, width, and direction.
 * The paddle's direction determines the movement direction, with -1 representing left and 1 representing right.
 * The Paddle class also provides methods to reset the direction and update the paddle's position based on the given deltaTime.
 */
#pragma once

class Game;

class Paddle
{
private:
    const float m_x;

protected:
    float m_y {};
    int m_direction {-1};
    float m_height {};
    float m_width {0};
    Game* m_game;

public:
    Paddle(Game* game, float height, float width);

    const float getX() const { return m_x; }
    const float getY() const { return m_y; }
    float getHeight() const { return m_height; }
    float getWidth() const { return m_width; }
    float getDirection() const { return m_direction; }
    void setGame(Game* game) { m_game = game; }
    
    void resetDirection();
    void setDirection(int dir);
    void update(float deltaTime);
};