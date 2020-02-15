#include "DrawComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Math.hpp"
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
    glm::mat4 scale_mat = mat::createScale(
        static_cast<float>(texture_width_),
        static_cast<float>(texture_height_),
        1.0f
    );
    glm::mat4 world = scale_mat * owner_->getWorldTransform();

    shader->setMatUniform("world_transform", world);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void DrawComponent::setTexture(SDL_Texture* texture)
{
    texture_ = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &texture_width_, &texture_height_);
}