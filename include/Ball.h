/**
 * @class Ball
 * @brief Represents a ball in the game.
 * 
 * The Ball class is responsible for managing the properties and behavior of a ball in the game.
 * It keeps track of the ball's position, width, speed, and whether it has collided with other game objects.
 * The ball can collide with the paddle, walls, and tiles.
 */
#pragma once

#include <vector>
#include "SDL.h"
#include "Game.h"

class Game;
class Tile;
class Paddle;
class PaddleAI;

class Ball
{
private:
    float m_x {};
    float m_y {};
    float m_width {};
    struct speed
    {
        float x;
        float y;
    };
    speed m_speed {};
    bool m_tileBroken {};
    Game* m_game;

public:
    Ball(float width, speed speed, Game* game);
    float getX() const {return m_x;}
    float getY() const {return m_y;}
    float getWidth() const {return m_width;}
    speed getSpeed() const {return m_speed;}
    bool getTileBroken() {return m_tileBroken;}
    void update(float deltaTime);
    bool detectCollisionWithPaddle(const Paddle* paddle, const PaddleAI* paddleAI);
    void collideWithWall();
    void collideWithPaddle();
    void collideWithTile(std::vector<Tile>& tiles);
    int ballOffScreen();
    void drawBall(SDL_Renderer* renderer, int centerX, int centerY, int radius);
};