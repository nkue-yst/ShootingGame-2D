#pragma once

class Vec2
{
public:
    Vec2()
        :x_(0.0f)
        ,y_(0.0f)
    {}

    explicit Vec2(float x, float y)
        :x_(x)
        ,y_(y)
    {}

    float x_;
    float y_;

    static const Vec2 ZERO;

    friend Vec2 operator+(const Vec2& a, const Vec2& b)
    {
        return Vec2(a.x_ + b.x_, a.y_ + b.y_);
    }

    friend Vec2 operator-(const Vec2& a, const Vec2& b)
    {
        return Vec2(a.x_ - b.x_, a.y_ - b.y_);
    }

    friend Vec2 operator*(const Vec2& a, const Vec2& b)
    {
        return Vec2(a.x_ * b.x_, a.y_ * b.y_);
    }

    friend Vec2 operator*(const Vec2& vec, float scalar)
    {
        return Vec2(vec.x_ * scalar, vec.y_ * scalar);
    }

    Vec2& operator+=(const Vec2& right)
    {
        x_ += right.x_;
        y_ += right.y_;
        return *this;
    }
};