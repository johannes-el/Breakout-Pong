/**
 * @class Tile
 * @brief Represents a tile in the game.
 * 
 * The Tile class is responsible for storing the position, size, color, and game reference of a tile.
 * It provides methods to access and modify the tile's properties.
 */
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
    int m_color;
    Game* m_game;

public:
    Tile(Game* game, float x, float y, float width, float height, int color)
    : m_x{x}, m_y{y}, m_width{width}, m_height{height}, m_game{game}, m_color{color} {}

    const float getX() const { return m_x; }
    const float getY() const { return m_y; }
    const float getWidth() const { return m_width; }
    const float getHeight() const { return m_height; }
    const int getColor() const { return m_color; }
    void setGame(Game* game) { this->m_game = game; }

};