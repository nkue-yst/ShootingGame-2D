#pragma once
#include "MoveComponent.hpp"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
    InputComponent(class Actor* owner);

    void inputKeys(const uint8_t* key_state) override;

    float getMaxForwardSpeed() const { return max_forward_speed_; }
    float getMaxAngularSpeed() const { return max_angular_speed_; }
    int getForwardKey() const { return forward_key_; }
    int getBackKey() const { return back_key_; }
    int getClockWiseKey() const { return clock_wise_key_; }
    int getCounterClockWiseKey() const { return counter_clock_wise_key_; }

    void setMaxForwardSpeed(float speed) { max_forward_speed_ = speed; }
    void setMaxAngularSpeed(float speed) { max_angular_speed_ = speed; }
    void setForwardKey(int key) { forward_key_ = key; }
    void setBackKey(int key) { back_key_ = key; }
    void setClockWiseKey(int key) { clock_wise_key_ = key; }
    void setCounterClockWiseKey(int key) { counter_clock_wise_key_ = key; }

private:
    float max_forward_speed_;
    float max_angular_speed_;

    int forward_key_;
    int back_key_;
    int clock_wise_key_;
    int counter_clock_wise_key_;
};