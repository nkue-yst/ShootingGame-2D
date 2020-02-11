#pragma once
#include <vector>
#include <SDL.h>

class Game
{
public:
    Game();

    bool initialize();
    void run();
    void shutdown();

    void addActor(class Actor* actor);
    void removeActor(class Actor* actor);

private:
    void inputKeys();
    void updateGame();
    void draw();

    std::vector<class Actor*> actors_;
    std::vector<class Actor*> waiting_actors_;

    SDL_Window* window_;
    SDL_GLContext context_;
    Uint32 ticks_count_;
    bool is_running_;
    bool is_updating_actor_;
};