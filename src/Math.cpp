#include "Math.hpp"

using std::cos;
using std::sin;

const vec2 vec2::ZERO(0.0f, 0.0f);

static float m4_identity[4][4] =
{
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};
const mat4 mat4::Identity(m4_identity);

mat4 mat4::createScale(float x_scale, float y_scale, float z_scale)
{
    float res[4][4] =
    {
        { x_scale,    0.0f,    0.0f, 0.0f },
        {    0.0f, y_scale,    0.0f, 0.0f },
        {    0.0f,    0.0f, z_scale, 0.0f },
        {    0.0f,    0.0f,    0.0f, 1.0f }
    };
    return mat4(res);
}

mat4 mat4::rotationZ(float theta)
{
    float res[4][4] =
    {
        {  cos(theta), sin(theta), 0.0f, 0.0f },
        { -sin(theta), cos(theta), 0.0f, 0.0f },
        {        0.0f,       0.0f, 1.0f, 0.0f },
        {        0.0f,       0.0f, 0.0f, 1.0f }
    };
    return mat4(res);
}

mat4 mat4::translation(const vec3& trans)
{
    float res[4][4] =
    {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { trans.x_, trans.y_, trans.z_, 1.0f }
    };
    return mat4(res);
}

mat4 mat4::createSimpleView(float width, float height)
{
    float res[4][4] =
    {
        { 2.0f/width,        0.0f, 0.0f, 0.0f },
        {       0.0f, 2.0f/height, 0.0f, 0.0f },
        {       0.0f,        0.0f, 1.0f, 0.0f },
        {       0.0f,        0.0f, 1.0f, 1.0f }
    };
    return mat4(res);
}