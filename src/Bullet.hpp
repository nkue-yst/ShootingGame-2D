#pragma once
#include "Actor.hpp"

class Bullet : public Actor
{
public:
    Bullet(class Game* game);

    void updateActor(float dt) override;

    float getRadius() const { return radius_; }
    void setRadius(float radius) { radius_ = radius; }

private:
    float life_time_;
    float radius_;
};