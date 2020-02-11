#pragma once
#include "Component.hpp"

class MoveComponent : public Component
{
public:
    MoveComponent(class Actor* owner, int update_order = 10);

    void update(float dt) override;

    float getAngularSpeed() const { return angular_speed_; }
    float getForwardSpeed() const { return forward_speed_; }
    void setAngularSpeed(float speed) { angular_speed_ = speed; }
    void setForwardSpeed(float speed) { forward_speed_ = speed; }

private:
    float angular_speed_;  // rad/sec
    float forward_speed_;
};