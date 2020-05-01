#pragma once
#include "Actor.hpp"
#include <cstdint>

class PlayerActor : public Actor
{
public:
    PlayerActor(class Game* game);

    void updateActor(float dt) override;
    void actorInput(const uint8_t* key_state) override;
};