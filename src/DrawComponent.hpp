#pragma once
#include <SDL.h>
#include "Component.hpp"

class DrawComponent : public Component
{
public:
    DrawComponent(class Actor* owner, int draw_order = 100);
    ~DrawComponent();

    virtual void draw(class Shader* shader);
    virtual void setTexture(SDL_Texture* texture);
    
    int getDrawOrder() const { return draw_order_; }
    int getTextureWidth() const { return texture_width_; }
    int getTextureHeight() const { return texture_height_; }

protected:
    SDL_Texture* texture_;
    int draw_order_;
    int texture_width_;
    int texture_height_;
};