#include "TestActor.hpp"
#include "DrawComponent.hpp"
#include "Game.hpp"

TestActor::TestActor(Game* game)
    :Actor(game)
{
    DrawComponent* dc = new DrawComponent(this, 150);
    dc->setTexture(game->getTexture("D:/source/code-master/Chapter05/Assets/Ship.png"));
}
