#include "Bullet.hpp"
#include "CircleCollisionComponent.hpp"
#include "DrawComponent.hpp"
#include "Game.hpp"
#include "MoveComponent.hpp"
#include "PlayerActor.hpp"

Bullet::Bullet(Game* game)
    :Actor(game)
    ,radius_(10.0f)
{
    DrawComponent* d_compo = new DrawComponent(this);
    d_compo->setTexture(game->getTexture("image/bullet.png"));

    MoveComponent* m_compo = new MoveComponent(this);
    m_compo->setForwardSpeed(500.0f);

    collision_ = new CircleCollisionComponent(this);
    collision_->setRadius(10.0f);
}

void Bullet::updateActor(float dt)
{

}
