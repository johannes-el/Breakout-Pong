#include "TileFactory.h"
#include "Game.h"

TileFactory::TileFactory(Game* game) : m_game{game} {}

std::vector<Tile> TileFactory::generateTiles()
{
    // Tile(Game* game, float x, float y, float width, float height)
    return {

    Tile(m_game, m_game->getWindowWidth()/2 + 150, 45, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 250, 45, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 350, 45, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 450, 45, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 550, 45, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 650, 45, 70, 160),

    Tile(m_game, m_game->getWindowWidth()/2 + 150, 235, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 250, 235, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 350, 235, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 450, 235, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 550, 235, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 650, 235, 70, 160),

    Tile(m_game, m_game->getWindowWidth()/2 + 150, 425, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 250, 425, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 350, 425, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 450, 425, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 550, 425, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 650, 425, 70, 160),

    Tile(m_game, m_game->getWindowWidth()/2 + 150, 615, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 250, 615, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 350, 615, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 450, 615, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 550, 615, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 650, 615, 70, 160),

    Tile(m_game, m_game->getWindowWidth()/2 + 150, 805, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 250, 805, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 350, 805, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 450, 805, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 550, 805, 70, 160),
    Tile(m_game, m_game->getWindowWidth()/2 + 650, 805, 70, 160),

    };
}