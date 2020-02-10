#pragma once
#include <SDL.h>

class Game
{
public:
    Game();

    bool initialize();
    void run();
    void shutdown();

private:
    void processInput();
    void updateGame();
    void generateOutput();

    SDL_Window* window_;
    bool isRunning_;
};