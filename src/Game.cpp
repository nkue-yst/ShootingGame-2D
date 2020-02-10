#include "Game.hpp"
#include <SDL.h>

Game::Game()
    :window_(nullptr)
    , isRunning_(true)
{

}

bool Game::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("SDLを初期化できませんでした. : %s", SDL_GetError());
        return false;
    }

    window_ = SDL_CreateWindow(
        "Game window",
        100,
        100,
        1080,
        720,
        0
    );

    if (!window_)
    {
        SDL_Log("ウィンドウの作成に失敗しました. : %s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::run()
{
    while (isRunning_)
    {
        //processInput();
        //updateGame();
        //generateOutput();
    }
}

void Game::shutdown()
{
    SDL_DestroyWindow(window_);
    SDL_Quit();
}