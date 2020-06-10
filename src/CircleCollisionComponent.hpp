#pragma once
#include "Component.hpp"
#include "Math.hpp"

class CircleCollisionComponent : public Component
{
public:
	CircleCollisionComponent(class Actor* owner);

	void setRadius(float rad) { radius_ = rad; }
	float getRadius() const { return radius_; }

	const Vec2& getCenter() const;

private:
	float radius_;
};

bool isColliding(const CircleCollisionComponent& a, const CircleCollisionComponent& b);