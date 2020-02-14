#include "Game.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Actor.hpp"
#include "DrawComponent.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

Game::Game()
    :actors_(NULL)
    ,shader_(nullptr)
    ,verts_(nullptr)
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
        SDL_Log("Failed to initialize SDL2 : %s", SDL_GetError());
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

    if (!window_)
    {
        SDL_Log("Failed to create window. : %s", SDL_GetError());
        return false;
    }

    context_ = SDL_GL_CreateContext(window_);

    // GLEWの初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }
    glGetError();    

    // シェーダ読み込み
    if (!loadShaders())
    {
        SDL_Log("Failed to load shaders.");
        return false;
    }

    // 描画物の作成
    createVerts();
    loadData();

    ticks_count_ = SDL_GetTicks();

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
        ;

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
    shader_->setActive();
    verts_->setActive();

    for (auto component : d_components_)
    {
        component->draw(shader_);
    }

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

void Game::addDrawComponent(class DrawComponent* d_component)
{
    int own_draw_order = d_component->getDrawOrder();
    auto iter = d_components_.begin();
    for (; iter != d_components_.end(); ++iter)
    {
        if (own_draw_order < (*iter)->getDrawOrder())
        {
            break;
        }
    }

    d_components_.insert(iter, d_component);
}

void Game::removeDrawComponent(class DrawComponent* d_component)
{
    auto iter = std::find(d_components_.begin(), d_components_.end(), d_component);
    d_components_.erase(iter);
}

bool Game::loadShaders()
{
    shader_ = new Shader();
    if (!shader_->load("src/shader/Basic.vert", "src/shader/Basic.frag"))
    {
        return false;
    }

    shader_->setActive();
    return true;
}

void Game::createVerts()
{
    float vertices[] = {
        -0.5f,  0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    verts_ = new VertexArray(vertices, 4, indices, 6);
}

void Game::loadData()
{
    ta_ = new TestActor(this);
    ta_ = new TestActor(this);
    ta_->setPosition(glm::vec2(100.0f, 100.0f));
}

SDL_Texture* Game::getTexture(const std::string& file_name)
{
    SDL_Texture* tex = nullptr;

    auto iter = textures_.find(file_name);
    if (iter != textures_.end())
    {
        tex = iter->second;
    }
    else
    {
        // Load image from file
    }
    return tex;
}