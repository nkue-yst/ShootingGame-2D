#include "Actor.hpp"
#include "Component.hpp"
#include "Game.hpp"

Actor::Actor(Game* game)
    :state_(EActive)
    ,need_recompute_world_transform_(true)
    ,position_(glm::vec2(0, 0))
    ,rotation_(0.0f)
    ,scale_(0.0f)
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
    if (state_ == EActive)
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

void Actor::updateActor(float dt)
{

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

        world_translation_ = math::createScale(scale_);
        world_translation_ *= math::createRotationZ(rotation_);
        world_translation_ *= math::createTranslation(glm::vec3(position_.x, position_.y, 0.0f));

        // 各コンポーネントにワールド変換を通知
        for (auto compo : components_)
        {
            compo->onUpdateWorldTransform();
        }
    }
}