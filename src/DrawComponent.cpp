#include "DrawComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Shader.hpp"

DrawComponent::DrawComponent(class Actor* owner, int draw_order)
    :Component(owner)
    ,texture_(nullptr)
    ,draw_order_(draw_order)
    ,texture_width_(0)
    ,texture_height_(0)
{
    owner_->getGame()->addDrawComponent(this);
}

DrawComponent::~DrawComponent()
{
    owner_->getGame()->removeDrawComponent(this);
}

void DrawComponent::draw(class Shader* shader)
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void DrawComponent::setTexture(SDL_Texture* texture)
{
    texture_ = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &texture_width_, &texture_height_);
}