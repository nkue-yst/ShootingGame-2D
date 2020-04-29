#pragma once
#include "Actor.hpp"
#include <cstdint>

class TestActor : public Actor
{
public:
    TestActor(class Game* game);

    void updateActor(float dt) override;
    void actorInput(const uint8_t* key_state) override;
};