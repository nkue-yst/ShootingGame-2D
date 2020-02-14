#include "Math.hpp"

using std::cos;
using std::sin;

glm::mat4 math::createScale(float x_scale, float y_scale, float z_scale)
{
    return glm::mat4(
        x_scale, 0.0f, 0.0f, 0.0f,
        0.0f, y_scale, 0.0f, 0.0f,
        0.0f, 0.0f, z_scale, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

glm::mat4 math::createScale(const float scale)
{
    return createScale(scale, scale, scale);
}

glm::mat4 math::createRotationX(float theta)
{
    return glm::mat4(
        1.0f,        0.0f,       0.0f, 0.0f,
        0.0f,  cos(theta), sin(theta), 0.0f,
        0.0f, -sin(theta), cos(theta), 0.0f,
        0.0f,        0.0f,       0.0f, 1.0f
    );
}

glm::mat4 math::createRotationY(float theta)
{
    return glm::mat4(
        cos(theta), 0.0f, -sin(theta), 0.0f,
              0.0f, 1.0f,        0.0f, 0.0f,
        sin(theta), 0.0f,  cos(theta), 0.0f,
              0.0f, 0.0f,        0.0f, 1.0f
    );
}

glm::mat4 math::createRotationZ(float theta)
{
    return glm::mat4(
         cos(theta), sin(theta), 0.0f, 0.0f,
        -sin(theta), cos(theta), 0.0f, 0.0f,
               0.0f,       0.0f, 1.0f, 0.0f,
               0.0f,       0.0f, 0.0f, 1.0f
    );
}

