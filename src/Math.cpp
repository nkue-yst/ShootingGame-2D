#include "Math.hpp"

using std::cos;
using std::sin;

const vec2 vec2::ZERO(0.0f, 0.0f);

float m4_identity[4][4] =
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
    float mat[4][4] =
    {
        {  cos(theta), sin(theta), 0.0f, 0.0f },
        { -sin(theta), cos(theta), 0.0f, 0.0f },
        {        0.0f,       0.0f, 1.0f, 0.0f },
        {        0.0f,       0.0f, 0.0f, 1.0f }
    };
    return mat4(mat);
}

mat4 mat4::translation(float x, float y, float z)
{
    float res[4][4] =
    {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        {    x,    y,    z, 1.0f }
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