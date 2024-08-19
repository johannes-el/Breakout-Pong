#pragma once

#include "Paddle.h"

class Ball;

class PaddleAI : public Paddle
{
private:
    const float m_x;
    Ball* ball;

public:
    PaddleAI(Game* game, Ball* ball);
    void setDirection();
    void update(float deltaTime);
    const float getX() const { return m_x; }
    // void handleWindowResize();
};