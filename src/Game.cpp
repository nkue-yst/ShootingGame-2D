#include "Game.hpp"
#include <GL/glew.h>
#include "Actor.hpp"

Game::Game()
    :actors_(NULL)
    ,window_(nullptr)
    ,context_(NULL)
    ,ticks_count_(0)
    ,is_running_(true)
    ,is_updating_actor_(false)
{

}

bool Game::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("SDLを初期化できませんでした. : %s", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    window_ = SDL_CreateWindow(
        "Game window",
        100,
        100,
        1280,
        720,
        SDL_WINDOW_OPENGL
    );
    context_ = SDL_GL_CreateContext(window_);

    // GLEWの初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_Log("GLEWの初期化に失敗しました.");
        return false;
    }
    glGetError();

    if (!window_)
    {
        SDL_Log("ウィンドウの作成に失敗しました. : %s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::run()
{
    while (is_running_)
    {
        inputKeys();
        updateGame();
        draw();
    }
}

void Game::shutdown()
{
    SDL_GL_DeleteContext(context_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Game::inputKeys()
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        switch (ev.type)
        {
            case SDL_QUIT:
                is_running_ = false;
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        is_running_ = false;
    }
}

void Game::updateGame()
{
    // フレーム制限(60FPS)
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_count_ + 16))
    {
    }

    float dt = (SDL_GetTicks() - ticks_count_) / 1000.0f;
    if (dt > 0.05f)
    {
        dt = 0.05f;
    }
    ticks_count_ = SDL_GetTicks();

    // 全アクターの更新
    is_updating_actor_ = true;
    for (auto actor : actors_)
    {
        actor->update(dt);
    }
    is_updating_actor_ = false;

    // 待機アクターをactors_に移動
    for (auto actor : waiting_actors_)
    {
        actors_.emplace_back(actor);
    }
    waiting_actors_.clear();

    // 死んだアクターを一時保存
    std::vector<Actor*> dead_actors;

    for (auto actor : actors_)
    {
        if (actor->getState() == Actor::EDead)
        {
            dead_actors.emplace_back(actor);
        }
    }

    // 死んだアクターを削除
    for (auto actor : dead_actors)
    {
        delete actor;
    }
}

void Game::draw()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw game

    SDL_GL_SwapWindow(window_);
}

void Game::addActor(Actor* actor)
{
    if (is_updating_actor_)
    {
        waiting_actors_.emplace_back(actor);
    }
    else
    {
        actors_.emplace_back(actor);
    }
}

void Game::removeActor(Actor* actor)
{
    auto iter = std::find(waiting_actors_.begin(), waiting_actors_.end(), actor);
    if (iter != waiting_actors_.end())
    {
        std::iter_swap(iter, waiting_actors_.end() - 1);
        waiting_actors_.pop_back();
    }

    iter = std::find(actors_.begin(), actors_.end(), actor);
    if (iter != actors_.end())
    {
        std::iter_swap(iter, actors_.end() - 1);
        actors_.pop_back();
    }
}