#pragma once

class Game;
class Ball;

class Tile
{
private:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
    Game* m_game;

public:
    Tile(Game* game, float x, float y, float width, float height)
    : m_x{x}, m_y{y}, m_width{width}, m_height{height}, m_game{game} {}

    const float getX() const { return m_x; }
    const float getY() const { return m_y; }
    const float getWidth() const { return m_width; }
    const float getHeight() const { return m_height; }
    void setGame(Game* game) { this->m_game = game; }
    // void handleWindowResize();

};