#pragma once

#include <SDL.h>
#include "Paddle.h"
#include "Ball.h"
#include <iostream>
#include "TileFactory.h"
#include <vector>
// #include "PaddleAI.h"

class Ball;
class PaddleAI;
class Tile;

class Game
{
private:
    SDL_Window* m_window;
    int m_windowWidth;
    int m_windowHeight;
    SDL_Renderer* m_renderer;
    bool m_isRunning;
    int m_ticksCount {0};
    Ball* m_ball;
    Paddle* m_paddle;
    PaddleAI* m_paddleAI;
    std::vector<Tile> tiles {};
    // PaddleAI m_paddleAI;

public:
    Game(Ball* ball, Paddle* paddle, PaddleAI* paddleAI) : m_ball(ball), m_paddle(paddle), m_paddleAI(paddleAI) {}
    int getWindowWidth() const {return m_windowWidth;}
    int getWindowHeight() const {return m_windowHeight;}
    void setBall(Ball* ball) {this->m_ball = ball;}
    void setPaddle(Paddle* paddle) {this->m_paddle = paddle;}
    void setPaddleAI(PaddleAI* paddleAI) {this->m_paddleAI = paddleAI;}

    bool initialize();
    void runLoop();
    void shutdown();
    void processInput();
    void updateGame();
    void generateOutput();
};

