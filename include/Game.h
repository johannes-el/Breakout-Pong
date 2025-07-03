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

enum class GameState
{
    MENU,
    RUNNING,
    PAUSED,
    GAME_OVER,
    QUIT,
};

class Game
{
public:
    explicit Game(bool debugMode) : m_debugMode(debugMode) {};
    float getWindowWidth() const { return m_windowWidth; }
    float getWindowHeight() const { return m_windowHeight; }
    const Paddle* getPaddle() const { return m_paddle; }
    const PaddleAI* getPaddleAI() const { return m_paddleAI; }
    void setBall(Ball* ball) { this->m_ball = ball; }
    void setPaddle(Paddle* paddle) { this->m_paddle = paddle; }
    void setPaddleAI(PaddleAI* paddleAI) { this->m_paddleAI = paddleAI; }

    bool initialize();
    void runLoop();
    void shutdown();
    void processInput();
    void updateGame();
    void generateOutput();
    void drawRunning();

private:
    SDL_Window* m_window;
    int m_windowWidth;
    int m_windowHeight;
    SDL_Renderer* m_renderer;
    bool m_isRunning {true};
    int m_ticksCount {0};
    Ball* m_ball = nullptr;
    Paddle* m_paddle = nullptr;
    PaddleAI* m_paddleAI = nullptr;
    std::vector<Tile> m_tiles {};

    GameState m_state = GameState::MENU; // initial state
    bool m_pausedPrevious {false};
    bool m_paused {false};
    bool m_debugMode;
};
