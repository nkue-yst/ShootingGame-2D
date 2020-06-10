#include "MoveComponent.hpp"
#include "Actor.hpp"
#include "Math.hpp"

MoveComponent::MoveComponent(class Actor* owner, int update_order)
    :Component(owner, update_order)
    ,angular_speed_(0.0f)
    ,forward_speed_(0.0f)
{

}

/* 親アクターの座標更新 */
void MoveComponent::update(float dt)
{
    float rot = owner_->getRotation();
    rot += angular_speed_ * dt;
    owner_->setRotation(rot);

    Vec2 pos = owner_->getPosition();
    pos += owner_->getForward() * forward_speed_ * dt;

    /* 画面端でワープ */
    if (owner_->getIsPlayer())
    {
        if (pos.x < -960.0f)
        {
            pos.x = 960.0f;
        }
        else if (pos.x > 960.0f)
        {
            pos.x = -960.0f;
        }

        if (pos.y < -540.0f)
        {
            pos.y = 540.0f;
        }
        else if (pos.y > 540.0f)
        {
            pos.y = -540.0f;
        }
    }
    else
    {
        if (pos.x < -960.0f || pos.x > 960.0f || pos.y < -540.0f || pos.y > 540.0f)
        {
            owner_->setState(Actor::State::EDead);
        }
    }

    owner_->setPosition(pos);
}