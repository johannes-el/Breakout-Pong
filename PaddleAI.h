#include "Paddle.h"

class Game;
class Ball;

class PaddleAI : public Paddle
{
private:
    Game* game;
    Ball* ball;
public:
    PaddleAI(Game* game, Ball* ball) : Paddle(game), ball(ball) {}
    void setDirection() {
        if (ball->getY() > m_y)
        {
            m_direction = 1;
        }
        else if (ball->getY() < m_y)
        {
            m_direction = -1;
        }
        else
        {
            m_direction = 0;
        }
    }
    // void update(float deltaTime);
};