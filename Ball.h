#pragma once

class Game;
class Paddle;
class PaddleAI;

class Ball
{
private:
    const Game* m_game;
    const Paddle* m_paddle;
    const PaddleAI* m_paddleAI;
    float m_x {1024.0f / 2.0f};
    float m_y {768.0f / 2.0f};
    struct speed
    {
        float x;
        float y;
    };
    speed m_speed {-200.0f, 235.0f};

public:
    Ball(const Game* game, const Paddle* paddle, const PaddleAI* paddleAI) : m_game(game), m_paddle(paddle), m_paddleAI(paddleAI) {}
    float getX() const {return m_x;}
    float getY() const {return m_y;}
    // set game
    void setGame(const Game* game) {this->m_game = game;}
    // set paddle
    void setPaddle(const Paddle* paddle) {this->m_paddle = paddle;}
    // set paddleAI
    void setPaddleAI(const PaddleAI* paddleAI) {this->m_paddleAI = paddleAI;}
    void update(float deltaTime);
    void collideWithWall();
    void collideWithPaddle();
    bool ballOffScreen();
};