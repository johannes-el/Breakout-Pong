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

class Game;
class Paddle;
class PaddleAI;
class Tile;

class Ball
{
private:
    const Game* m_game;
    const Paddle* m_paddle;
    const PaddleAI* m_paddleAI;
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

public:
    Ball(float width, speed speed, const Game* game, const Paddle* paddle, const PaddleAI* paddleAI);
    float getX() const {return m_x;}
    float getY() const {return m_y;}
    float getWidth() const {return m_width;}
    speed getSpeed() const {return m_speed;}
    bool getTileBroken() {return m_tileBroken;}
    void setGame(const Game* game) {this->m_game = game;}
    void setPaddle(const Paddle* paddle) {this->m_paddle = paddle;}
    void setPaddleAI(const PaddleAI* paddleAI) {this->m_paddleAI = paddleAI;}
    void update(float deltaTime);
    bool detectCollisionWithPaddle();
    void collideWithWall();
    void collideWithPaddle();
    void collideWithTile(std::vector<Tile>& tiles);
    bool ballOffScreen();
    void drawBall(SDL_Renderer* renderer, int centerX, int centerY, int radius);
};