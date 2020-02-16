#pragma once
#include <cmath>
#include <memory>

class vec2
{
public:
    float x_;
    float y_;

    static const vec2 ZERO;

    vec2()
        :x_(0.0f)
        ,y_(0.0f)
    {}

    explicit vec2(float x, float y)
        :x_(x)
        ,y_(y)
    {}

	friend vec2 operator+(const vec2& a, const vec2& b)
	{
		return vec2(a.x_ + b.x_, a.y_ + b.y_);
	}

	friend vec2 operator*(const vec2& vec, float scalar)
	{
		return vec2(vec.x_ * scalar, vec.y_ * scalar);
	}

	vec2& operator+=(const vec2& right)
	{
		x_ += right.x_;
		y_ += right.y_;
		return *this;
	}
};

class mat4
{
public:
	float mat_[4][4];
	static const mat4 Identity;

	// 単位行列で初期化
	mat4() { *this = mat4::Identity; }

	explicit mat4(float mat[4][4])
	{
		memcpy(mat_, mat, 16 * sizeof(float));
	}

	friend mat4 operator*(const mat4& a, const mat4& b)
	{
		mat4 res;
		// Row 0
		res.mat_[0][0] =
			a.mat_[0][0] * b.mat_[0][0] + a.mat_[0][1] * b.mat_[1][0] +
			a.mat_[0][2] * b.mat_[2][0] + a.mat_[0][3] * b.mat_[3][0];

		res.mat_[0][1] =
			a.mat_[0][0] * b.mat_[0][1] + a.mat_[0][1] * b.mat_[1][1] +
			a.mat_[0][2] * b.mat_[2][1] + a.mat_[0][3] * b.mat_[3][1];

		res.mat_[0][2] =
			a.mat_[0][0] * b.mat_[0][2] + a.mat_[0][1] * b.mat_[1][2] +
			a.mat_[0][2] * b.mat_[2][2] + a.mat_[0][3] * b.mat_[3][2];

		res.mat_[0][3] =
			a.mat_[0][0] * b.mat_[0][3] + a.mat_[0][1] * b.mat_[1][3] +
			a.mat_[0][2] * b.mat_[2][3] + a.mat_[0][3] * b.mat_[3][3];

		// Row 1
		res.mat_[1][0] =
			a.mat_[1][0] * b.mat_[0][0] + a.mat_[1][1] * b.mat_[1][0] +
			a.mat_[1][2] * b.mat_[2][0] + a.mat_[1][3] * b.mat_[3][0];

		res.mat_[1][1] =
			a.mat_[1][0] * b.mat_[0][1] + a.mat_[1][1] * b.mat_[1][1] +
			a.mat_[1][2] * b.mat_[2][1] + a.mat_[1][3] * b.mat_[3][1];

		res.mat_[1][2] =
			a.mat_[1][0] * b.mat_[0][2] + a.mat_[1][1] * b.mat_[1][2] +
			a.mat_[1][2] * b.mat_[2][2] + a.mat_[1][3] * b.mat_[3][2];

		res.mat_[1][3] =
			a.mat_[1][0] * b.mat_[0][3] + a.mat_[1][1] * b.mat_[1][3] +
			a.mat_[1][2] * b.mat_[2][3] + a.mat_[1][3] * b.mat_[3][3];

		// Row 2
		res.mat_[2][0] =
			a.mat_[2][0] * b.mat_[0][0] + a.mat_[2][1] * b.mat_[1][0] +
			a.mat_[2][2] * b.mat_[2][0] + a.mat_[2][3] * b.mat_[3][0];

		res.mat_[2][1] =
			a.mat_[2][0] * b.mat_[0][1] + a.mat_[2][1] * b.mat_[1][1] +
			a.mat_[2][2] * b.mat_[2][1] + a.mat_[2][3] * b.mat_[3][1];

		res.mat_[2][2] =
			a.mat_[2][0] * b.mat_[0][2] + a.mat_[2][1] * b.mat_[1][2] +
			a.mat_[2][2] * b.mat_[2][2] + a.mat_[2][3] * b.mat_[3][2];

		res.mat_[2][3] =
			a.mat_[2][0] * b.mat_[0][3] + a.mat_[2][1] * b.mat_[1][3] +
			a.mat_[2][2] * b.mat_[2][3] + a.mat_[2][3] * b.mat_[3][3];

		// Row 3
		res.mat_[3][0] =
			a.mat_[3][0] * b.mat_[0][0] + a.mat_[3][1] * b.mat_[1][0] +
			a.mat_[3][2] * b.mat_[2][0] + a.mat_[3][3] * b.mat_[3][0];

		res.mat_[3][1] =
			a.mat_[3][0] * b.mat_[0][1] + a.mat_[3][1] * b.mat_[1][1] +
			a.mat_[3][2] * b.mat_[2][1] + a.mat_[3][3] * b.mat_[3][1];

		res.mat_[3][2] =
			a.mat_[3][0] * b.mat_[0][2] + a.mat_[3][1] * b.mat_[1][2] +
			a.mat_[3][2] * b.mat_[2][2] + a.mat_[3][3] * b.mat_[3][2];

		res.mat_[3][3] =
			a.mat_[3][0] * b.mat_[0][3] + a.mat_[3][1] * b.mat_[1][3] +
			a.mat_[3][2] * b.mat_[2][3] + a.mat_[3][3] * b.mat_[3][3];

		return res;
	}

	mat4& operator*=(const mat4& right)
	{
		*this = *this * right;
		return *this;
	}

	// 行列のポインターを取得
	const float* getPointer() const { return reinterpret_cast<const float*>(&mat_[0][0]); }

    // スケール行列作成
    static mat4 createScale(float x_scale, float y_scale, float z_scale);
    static mat4 createScale(float scale) { return createScale(scale, scale, scale); }

    // 回転行列作成
    static mat4 rotationZ(float theta);

	// 平行移動行列
	static mat4 translation(float x, float y, float z);

	// 2Dビュー射影変換
	static mat4 createSimpleView(float width, float height);
};