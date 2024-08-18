#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "PaddleAI.h"

int main(int argc, char* argv[])
{
    // Step 1: Create Game object
    Game game(nullptr, nullptr, nullptr);

    // Step 2: Create Ball object, passing the Game object
    Ball ball(&game, nullptr, nullptr);

    // Step 3: Create Paddle object, passing the Game object
    Paddle paddle(&game);

    // Step 4: Create PaddleAI object, passing the Game and Ball objects
    PaddleAI paddleAI(&game, &ball);

    // Set the pointers in the Game object
    game.setBall(&ball);
    game.setPaddle(&paddle);
    game.setPaddleAI(&paddleAI);

    // Set the pointers in the Ball object
    ball.setPaddle(&paddle);
    ball.setPaddleAI(&paddleAI);

    

    // Initialize and run the game
    if (game.initialize())
    {
        game.runLoop();
    }

    game.shutdown();
    return 0;
}