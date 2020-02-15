#pragma once
#include "Component.hpp"

class DrawComponent : public Component
{
public:
    DrawComponent(class Actor* owner, int draw_order = 100);
    ~DrawComponent();

    virtual void draw(class Shader* shader);
    virtual void setTexture(class Texture* texture);
    
    int getTextureWidth() const { return texture_width_; }
    int getTextureHeight() const { return texture_height_; }
    int getDrawOrder() const { return draw_order_; }

protected:
    class Texture* texture_;
    int texture_width_;
    int texture_height_;

    int draw_order_;
};