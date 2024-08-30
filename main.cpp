#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "PaddleAI.h"

int main(int argc, char* argv[])
{
    Game game(nullptr, nullptr, nullptr); // Ball, Paddle, PaddleAI

    if (game.initialize())
    {
        // Set up the parameters for the game objects
        Ball ball(9, {300, 300}, &game); // width, speed (x, y), game
        Paddle paddle(&game, 100.0f, 15.0f); // game, height, width
        PaddleAI paddleAI(&game, &ball, 100.0f, 15.0f, 300.0f); // game, ball, height, width, speed
        game.setBall(&ball);
        game.setPaddle(&paddle);
        game.setPaddleAI(&paddleAI);
        game.runLoop();
    }
    else 
    {
        std::cerr << "Game initialization failed." << std::endl;
    }

    game.shutdown();
    return 0;
}