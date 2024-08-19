#pragma once

#include "Tile.h"
#include "Game.h"
#include <vector>

class Tile;

class TileFactory
{
private:
    Game* m_game;
    Tile* m_tile;
public:
    TileFactory(Game* game);
    std::vector<Tile> generateTiles();
};