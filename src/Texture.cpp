#include "Texture.hpp"
#include "GL/glew.h"
#include <SDL.h>
#include <SOIL.h>

Texture::Texture()
    :texture_id_(0)
    ,width_(0)
    ,height_(0)
{

}

Texture::~Texture()
{

}

/* SOILを用いてテクスチャのロード */
bool Texture::loadImage(const std::string& name)
{
    int channels_num = 0;
    unsigned char* image = SOIL_load_image(
        name.c_str(),
        &width_,
        &height_,
        &channels_num,
        SOIL_LOAD_AUTO
    );

    if (image == nullptr)
    {
        SDL_Log("Failed to load image %s.", name.c_str());
        return false;
    }

    int format = GL_RGB;
    if (channels_num == 4)
    {
        format = GL_RGBA;
    }

    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width_,
        height_,
        0,
        format,
        GL_UNSIGNED_BYTE,
        image
    );

    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void Texture::unLoadImage()
{
    glDeleteTextures(1, &texture_id_);
}

void Texture::setActive()
{
    glBindTexture(GL_TEXTURE_2D, texture_id_);
}