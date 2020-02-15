#pragma once
#include <string>

class Texture
{
public:
    Texture();
    ~Texture();

    bool loadImage(const std::string& name);
    void unLoadImage();

    void setActive();

    const int getWidth() const { return width_; }
    const int getHeight() const { return height_; }

private:
    unsigned int texture_id_;
    int width_;
    int height_;
};