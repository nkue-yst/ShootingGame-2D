#include "DrawComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Math.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

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
    texture_->setActive();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void DrawComponent::setTexture(class Texture* texture)
{
    texture_ = texture;
    texture_width_ = texture_->getWidth();
    texture_height_ = texture->getHeight();
}