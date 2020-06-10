#include "InputComponent.hpp"
#include "Actor.hpp"

InputComponent::InputComponent(class Actor* owner)
    :MoveComponent(owner)
    ,forward_key_(0)
    ,back_key_(0)
    ,clock_wise_key_(0)
    ,counter_clock_wise_key_(0)
{

}

/* ˆÚ“®E‰ñ“]‚Ì“ü—Í */
void InputComponent::inputKeys(const uint8_t* key_state)
{
    float forward_speed = 0.0f;
    if (key_state[forward_key_])
    {
        forward_speed += max_forward_speed_;
    }
    if (key_state[back_key_])
    {
        forward_speed -= max_forward_speed_;
    }
    setForwardSpeed(forward_speed);

    float angular_speed = 0.0f;
    if (key_state[clock_wise_key_])
    {
        angular_speed += max_angular_speed_;
    }
    if (key_state[counter_clock_wise_key_])
    {
        angular_speed -= max_angular_speed_;
    }
    setAngularSpeed(angular_speed);
}