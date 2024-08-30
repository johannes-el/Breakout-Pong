/**
 * @class Game
 * @brief Represents the game logic and functionality.
 * 
 * The Game class manages the game window, renderer, game objects, and game loop.
 * It handles user input, updates the game state, and generates the output.
 */
#pragma once

#include <SDL.h>
#include "Paddle.h"
#include "Ball.h"
#include <iostream>
#include "TileFactory.h"
#include <vector>

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
    bool m_isRunning {true};
    int m_ticksCount {0};
    Ball* m_ball;
    Paddle* m_paddle;
    PaddleAI* m_paddleAI;
    std::vector<Tile> m_tiles {};
    bool m_pausedPrevious {false};
    bool m_paused {false};

public:
    Game(Ball* ball, Paddle* paddle, PaddleAI* paddleAI) : m_ball(ball), m_paddle(paddle), m_paddleAI(paddleAI) {}
    float getWindowWidth() const {return m_windowWidth;}
    float getWindowHeight() const {return m_windowHeight;}
    const Paddle* getPaddle() const {return m_paddle;}
    const PaddleAI* getPaddleAI() const {return m_paddleAI;}
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

