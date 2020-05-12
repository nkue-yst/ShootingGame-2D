#include "MoveComponent.hpp"
#include "Actor.hpp"
#include "Math.hpp"

MoveComponent::MoveComponent(class Actor* owner, int update_order)
    :Component(owner, update_order)
    ,angular_speed_(0.0f)
    ,forward_speed_(0.0f)
{

}

void MoveComponent::update(float dt)
{
    float rot = owner_->getRotation();
    rot += angular_speed_ * dt;
    owner_->setRotation(rot);

    vec2 pos = owner_->getPosition();
    pos += owner_->getForward() * forward_speed_ * dt;
    if (pos.x_ < -900.0f)
    {
        pos.x_ = 900.0f;
    }
    else if (pos.x_ > 900.0f)
    {
        pos.x_ = -900.0f;
    }

    if (pos.y_ < -450.0f)
    {
        pos.y_ = 450.0f;
    }
    else if (pos.y_ > 450.0f)
    {
        pos.y_ = -450.0f;
    }
    owner_->setPosition(pos);
}