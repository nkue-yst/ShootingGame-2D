#include "Bullet.hpp"
#include "DrawComponent.hpp"
#include "Game.hpp"
#include "MoveComponent.hpp"

Bullet::Bullet(Game* game)
    :Actor(game)
    ,life_time_(1.0f)
    ,radius_(10.0f)
{
    DrawComponent* d_compo = new DrawComponent(this);
    d_compo->setTexture(game->getTexture("image/bullet.png"));

    MoveComponent* m_compo = new MoveComponent(this);
    m_compo->setForwardSpeed(500.0f);
}

void Bullet::updateActor(float dt)
{
    life_time_ -= dt;
    
    if (life_time_ <= 0.0f)
    {
        setState(Actor::State::EDead);
    }
}