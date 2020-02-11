#include "Actor.hpp"
#include "Game.hpp"

Actor::Actor(Game* game)
    :state_(EActive)
    ,position_(Vec2::ZERO)
    ,rotation_(0.0f)
    ,scale_(0.0f)
    ,game_(game)
{}

Actor::~Actor()
{
    game_->removeActor(this);

    while (!components_.empty())
    {
        delete components_.back();
    }
}

void Actor::update(float dt)
{

}

void Actor::removeComponent(Component* component)
{
    auto iter = std::find(components_.begin(), components_.end(), component);
    if (iter != components_.end())
    {
        components_.erase(iter);
    }
}