#pragma once

class Game;

class Paddle
{
private:
    const float m_x;

protected:
    float m_y {};
    float m_direction {0};
    const float m_height {100.0f};
    Game* game;

public:
    Paddle(Game* game);

    const float getX() const { return m_x; }
    const float getY() const { return m_y; }
    float getHeight() const { return m_height; }
    float getDirection() const { return m_direction; }
    void setGame(Game* game) { this->game = game; }
    
    void resetDirection();
    void setDirection(int dir);
    void update(float deltaTime);
};