#pragma once

#include <vector>

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
    struct speed
    {
        float x;
        float y;
    };
    speed m_speed {};
    bool m_tileBroken {};

public:
    Ball(const Game* game, const Paddle* paddle, const PaddleAI* paddleAI);
    float getX() const {return m_x;}
    float getY() const {return m_y;}
    speed getSpeed() const {return m_speed;}
    bool getTileBroken() {return m_tileBroken;}
    // set game
    void setGame(const Game* game) {this->m_game = game;}
    // set paddle
    void setPaddle(const Paddle* paddle) {this->m_paddle = paddle;}
    // set paddleAI
    void setPaddleAI(const PaddleAI* paddleAI) {this->m_paddleAI = paddleAI;}
    void update(float deltaTime);
    bool detectCollisionWithPaddle();
    void collideWithWall();
    void collideWithPaddle();
    void collideWithTile(std::vector<Tile>& tiles);
    bool ballOffScreen();
};