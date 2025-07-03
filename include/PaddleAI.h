/**
 * @file PaddleAI.h
 * @brief Header file for the PaddleAI class.
 * 
 * This file contains the declaration of the PaddleAI class, which is a derived class of the Paddle class.
 * The PaddleAI class represents an AI-controlled paddle in a game of Breakout Pong.
 * 
 * The PaddleAI class has a constant x-coordinate, a height, a speed, and a pointer to the Ball class.
 * It provides methods to set the direction of the paddle, update its position, and get its x-coordinate.
 */
#pragma once

#include "Paddle.h"

class Ball;

class PaddleAI : public Paddle
{
public:
    PaddleAI(Game* game, Ball* ball, float height, float width, float speed);
    void setDirection();
    void update(float deltaTime);
    const float getX() const { return m_x; }

private:
    const float m_x;
    float m_height;
    float m_speed;
    Ball* ball;
};
