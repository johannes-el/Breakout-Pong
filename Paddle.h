#pragma once

class Game;

class Paddle
{
protected:
    float m_x {10.0f};
    float m_y {768.0f / 2.0f};
    float m_direction {0};
    const float m_height {100.0f};
    Game* game;

public:
    Paddle(Game* game) : game(game) {}

    float getX() const { return m_x; }
    float getY() const { return m_y; }
    float getHeight() const { return m_height; }
    float getDirection() const { return m_direction; }
    void setGame(Game* game) { this->game = game; }
    
    void resetDirection();
    void setDirection(int dir);
    void update(float deltaTime);
};