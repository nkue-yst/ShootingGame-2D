#pragma once
#include <SDL.h>
#include <vector>

class Game
{
public:
    Game();

    bool initialize();
    void run();
    void shutdown();

    void addActor(class Actor* actor);
    void removeActor(class Actor* actor);

    void addDrawComponent(class DrawComponent* d_component);
    void removeDrawComponent(class DrawComponent* d_component);

    bool loadShaders();
    void createVerts();
    void loadData();

private:
    void inputKeys();
    void updateGame();
    void draw();

    std::vector<class Actor*> actors_;
    std::vector<class Actor*> waiting_actors_;

    std::vector<class DrawComponent*> d_components_;

    class Shader* shader_;
    class VertexArray* verts_;

    SDL_Window* window_;
    SDL_GLContext context_;
    Uint32 ticks_count_;
    bool is_running_;
    bool is_updating_actor_;
};