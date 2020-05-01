#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "Math.hpp"

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

    class Texture* getTexture(const std::string& file_name);

private:
    void inputKeys();
    void updateGame();
    void draw();
    bool loadShaders();
    void createVerts();
    void loadData();
    void unloadData();

    std::unordered_map<std::string, class Texture*> textures_;

    std::vector<class Actor*> actors_;
    std::vector<class Actor*> waiting_actors_;

    std::vector<class DrawComponent*> d_components_;
    class PlayerActor* player_;

    class Shader* shader_;
    class VertexArray* verts_;

    SDL_Window* window_;
    SDL_GLContext context_;
    Uint32 ticks_count_;
    bool is_running_;
    bool is_actor_updating_;
};