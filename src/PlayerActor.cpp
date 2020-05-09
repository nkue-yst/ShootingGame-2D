#include "PlayerActor.hpp"
#include "Bullet.hpp"
#include "DrawComponent.hpp"
#include "Game.hpp"
#include "InputComponent.hpp"

PlayerActor::PlayerActor(Game* game)
    :Actor(game)
{
    DrawComponent* dc = new DrawComponent(this, 150);
    dc->setTexture(game->getTexture("./image/player.png"));

    InputComponent* ic = new InputComponent(this);
    ic->setForwardKey(SDL_SCANCODE_W);
    ic->setBackKey(SDL_SCANCODE_S);
    ic->setClockWiseKey(SDL_SCANCODE_A);
    ic->setCounterClockWiseKey(SDL_SCANCODE_D);
    ic->setMaxForwardSpeed(300.0f);
    ic->setMaxAngularSpeed(3.1415f * 2.0f);
}

void PlayerActor::updateActor(float dt)
{

}

void PlayerActor::actorInput(const uint8_t* key_state)
{
    if (key_state[SDL_SCANCODE_SPACE])
    {
        Bullet* bullet = new Bullet(getGame());
        bullet->setPosition(getPosition());
        bullet->setRotation(getRotation());
    }
}