#include "CircleCollisionComponent.hpp"
#include "Actor.hpp"

CircleCollisionComponent::CircleCollisionComponent(class Actor* owner)
	:Component(owner)
	, radius_(0.0f)
{

}

const Vec2& CircleCollisionComponent::getCenter() const
{
	return owner_->getPosition();
}

bool isColliding(const CircleCollisionComponent& a, const CircleCollisionComponent& b)
{
	Vec2 middle = a.getCenter() - b.getCenter();
	float sqr_dist = middle.squared();

	float total_rad = a.getRadius() + b.getRadius();
	float sqr_total_rad = total_rad * total_rad;

	return (sqr_dist <= sqr_total_rad);
}