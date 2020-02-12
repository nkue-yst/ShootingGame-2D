#pragma once
#include "Actor.hpp"

class TestActor : public Actor
{
public:
    TestActor(class Game* game);

    void updateActor(float dt) override;
};