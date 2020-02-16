#include "Actor.hpp"
#include "Component.hpp"
#include "Game.hpp"

Actor::Actor(Game* game)
    :state_(Actor::State::EActive)
    ,world_translation_()
    ,need_recompute_world_transform_(true)
    ,position_(vec2::ZERO)
    ,rotation_(0.0f)
    ,scale_(1.0f)
    ,game_(game)
{
    game_->addActor(this);
}

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
    if (state_ == Actor::State::EActive)
    {
        computeWorldTransform();

        updateComponents(dt);
        updateActor(dt);

        computeWorldTransform();
    }
}

void Actor::updateComponents(float dt)
{
    for (auto component : components_)
    {
        component->update(dt);
    }
}

void Actor::addComponent(class Component* component)
{
    int own_order = component->getUpdateOrder();
    auto iter = components_.begin();
    for (; iter != components_.end(); ++iter)
    {
        if (own_order < (*iter)->getUpdateOrder())
        {
            break;
        }
    }

    components_.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
    auto iter = std::find(components_.begin(), components_.end(), component);
    if (iter != components_.end())
    {
        components_.erase(iter);
    }
}

void Actor::computeWorldTransform()
{
    if (need_recompute_world_transform_)
    {
        need_recompute_world_transform_ = false;

        world_translation_ = mat4::createScale(scale_);
        world_translation_ *= mat4::rotationZ(rotation_);
        world_translation_ *= mat4::translation(position_.x_, position_.y_, 0.0f);

        // 各コンポーネントにワールド変換を通知
        for (auto component : components_)
        {
            component->onUpdateWorldTransform();
        }
    }
}