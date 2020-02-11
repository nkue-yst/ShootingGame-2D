#include "Component.hpp"
#include "Actor.hpp"

Component::Component(class Actor* owner, int update_order)
    :owner_(owner)
    ,update_order_(update_order)
{}

Component::~Component()
{
    owner_->removeComponent(this);
}

void Component::update(float dt)
{

}