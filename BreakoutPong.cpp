#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "PaddleAI.h"

int main(int argc, char* argv[])
{
    // Step 1: Create Game object
    Game game(nullptr, nullptr, nullptr);

    // Initialize and run the game
    if (game.initialize())
    {
        Ball ball(&game, nullptr, nullptr);
        Paddle paddle(&game);
        PaddleAI paddleAI(&game, &ball);
        game.setBall(&ball);
        game.setPaddle(&paddle);
        game.setPaddleAI(&paddleAI);
        ball.setPaddle(&paddle);
        ball.setPaddleAI(&paddleAI);
        game.runLoop();
    }

    game.shutdown();
    return 0;
}