#include "TestActor.hpp"
#include "DrawComponent.hpp"
#include "Game.hpp"
#include "InputComponent.hpp"

TestActor::TestActor(Game* game)
    :Actor(game)
{
    DrawComponent* dc = new DrawComponent(this, 150);
    dc->setTexture(game->getTexture("./image/Ship.png"));

    InputComponent* ic = new InputComponent(this);
    ic->setForwardKey(SDL_SCANCODE_W);
    ic->setBackKey(SDL_SCANCODE_S);
    ic->setClockWiseKey(SDL_SCANCODE_A);
    ic->setCounterClockWiseKey(SDL_SCANCODE_D);
    ic->setMaxForwardSpeed(300.0f);
    ic->setMaxAngularSpeed(3.1415f * 2.0f);
}

void TestActor::updateActor(float dt)
{

}

void TestActor::actorInput(const uint8_t* key_state)
{

}