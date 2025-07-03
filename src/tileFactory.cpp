#include "TileFactory.h"
#include "Game.h"

TileFactory::TileFactory(Game* game) : m_game{game} {}

/**
 * Generates a vector of pre-defined Tile objects.
 * 
 * @return A vector of Tile objects.
 */
std::vector<Tile> TileFactory::generateTiles()
{
    // Tile(Game* game, float x, float y, float width, float height)
    float tileWidth = 81;
    float tileHeight = 2 * tileWidth;
    float x_offset = tileWidth + 1;
    float y_offset = tileHeight + 1;
    float alignmentConstantX = 250.0f;
    float alignmentConstantY = 1.0f;
    return
    {
        Tile(m_game, m_game->getWindowWidth()/2 + 0 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 0 * y_offset + alignmentConstantY, tileWidth, tileHeight, 0),
        Tile(m_game, m_game->getWindowWidth()/2 + 1 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 0 * y_offset + alignmentConstantY, tileWidth, tileHeight, 1),
        Tile(m_game, m_game->getWindowWidth()/2 + 2 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 0 * y_offset + alignmentConstantY, tileWidth, tileHeight, 2),
        Tile(m_game, m_game->getWindowWidth()/2 + 3 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 0 * y_offset + alignmentConstantY, tileWidth, tileHeight, 3),
        Tile(m_game, m_game->getWindowWidth()/2 + 4 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 0 * y_offset + alignmentConstantY, tileWidth, tileHeight, 4),
        Tile(m_game, m_game->getWindowWidth()/2 + 5 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 0 * y_offset + alignmentConstantY, tileWidth, tileHeight, 5),

        Tile(m_game, m_game->getWindowWidth()/2 + 0 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 0),
        Tile(m_game, m_game->getWindowWidth()/2 + 1 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 1),
        Tile(m_game, m_game->getWindowWidth()/2 + 2 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 2),
        Tile(m_game, m_game->getWindowWidth()/2 + 3 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 3),
        Tile(m_game, m_game->getWindowWidth()/2 + 4 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 4),
        Tile(m_game, m_game->getWindowWidth()/2 + 5 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 5),

        Tile(m_game, m_game->getWindowWidth()/2 + 0 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 0),
        Tile(m_game, m_game->getWindowWidth()/2 + 1 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 1),
        Tile(m_game, m_game->getWindowWidth()/2 + 2 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 2),
        Tile(m_game, m_game->getWindowWidth()/2 + 3 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 3),
        Tile(m_game, m_game->getWindowWidth()/2 + 4 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 4),
        Tile(m_game, m_game->getWindowWidth()/2 + 5 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 + 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 5),

        Tile(m_game, m_game->getWindowWidth()/2 + 0 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 0),
        Tile(m_game, m_game->getWindowWidth()/2 + 1 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 1),
        Tile(m_game, m_game->getWindowWidth()/2 + 2 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 2),
        Tile(m_game, m_game->getWindowWidth()/2 + 3 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 3),
        Tile(m_game, m_game->getWindowWidth()/2 + 4 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 4),
        Tile(m_game, m_game->getWindowWidth()/2 + 5 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 1 * y_offset + alignmentConstantY, tileWidth, tileHeight, 5),

        Tile(m_game, m_game->getWindowWidth()/2 + 0 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 0),
        Tile(m_game, m_game->getWindowWidth()/2 + 1 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 1),
        Tile(m_game, m_game->getWindowWidth()/2 + 2 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 2),
        Tile(m_game, m_game->getWindowWidth()/2 + 3 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 3),
        Tile(m_game, m_game->getWindowWidth()/2 + 4 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 4),
        Tile(m_game, m_game->getWindowWidth()/2 + 5 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 2 * y_offset + alignmentConstantY, tileWidth, tileHeight, 5),

        Tile(m_game, m_game->getWindowWidth()/2 + 0 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 3 * y_offset + alignmentConstantY, tileWidth, tileHeight, 0),
        Tile(m_game, m_game->getWindowWidth()/2 + 1 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 3 * y_offset + alignmentConstantY, tileWidth, tileHeight, 1),
        Tile(m_game, m_game->getWindowWidth()/2 + 2 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 3 * y_offset + alignmentConstantY, tileWidth, tileHeight, 2),
        Tile(m_game, m_game->getWindowWidth()/2 + 3 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 3 * y_offset + alignmentConstantY, tileWidth, tileHeight, 3),
        Tile(m_game, m_game->getWindowWidth()/2 + 4 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 3 * y_offset + alignmentConstantY, tileWidth, tileHeight, 4),
        Tile(m_game, m_game->getWindowWidth()/2 + 5 * x_offset + alignmentConstantX, m_game->getWindowHeight()/2 - 3 * y_offset + alignmentConstantY, tileWidth, tileHeight, 5),
    };
}