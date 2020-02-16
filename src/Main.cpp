#include "Game.hpp"

int main(int argc, char** argv)
{
    Game game;
    bool success = game.initialize();
    
    if (success)
    {
        game.run();
    }

    game.shutdown();

    return 0;
}