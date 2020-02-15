#include "TestActor.hpp"
#include "DrawComponent.hpp"
#include "Game.hpp"

TestActor::TestActor(Game* game)
    :Actor(game)
{
    DrawComponent* dc = new DrawComponent(this, 100);
}
