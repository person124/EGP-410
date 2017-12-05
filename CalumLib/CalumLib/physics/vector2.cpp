#include "vector2.h"

#include <cmath>

const float TWO_PI = 6.28318530718f;

Vector2 Vector2::toVector(float angle)
{
	return Vector2(cosf(angle), sinf(angle));
}

float Vector2::dot(Vector2& v1, Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

#include <iostream>
float Vector2::toAngle(Vector2& v)
{
	if (v.length() != 0)
	{
		float angle = atan2f(v.y, v.x);

		while (angle < 0)
			angle += TWO_PI;
		while (angle > TWO_PI)
			angle -= TWO_PI;

		return angle;
	}

	return 0.0f;
}

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float xVal, float yVal)
{
	x = xVal;
	y = yVal;
}

Vector2 Vector2::normal()
{
	return *this / length();
}

void Vector2::normalize()
{
	float len = length();
	x /= len;
	y /= len;
}

float Vector2::asAngle()
{
	return Vector2::toAngle(*this);
}

float Vector2::length()
{
	return sqrtf(x * x + y * y);
}

// Operator Overloads
Vector2& Vector2::operator=(Vector2& right)
{
	x = right.x;
	y = right.y;
	return *this;
}

Vector2& Vector2::operator+=(Vector2& right)
{
	x += right.x;
	y += right.y;
	return *this;
}

Vector2& Vector2::operator-=(Vector2& right)
{
	x -= right.x;
	y -= right.y;
	return *this;
}

Vector2& Vector2::operator+=(float right)
{
	x += right;
	y += right;
	return *this;
}

Vector2& Vector2::operator-=(float right)
{
	x -= right;
	y -= right;
	return *this;
}

Vector2& Vector2::operator*=(float right)
{
	x *= right;
	y *= right;
	return *this;
}

Vector2& Vector2::operator/=(float right)
{
	x /= right;
	y /= right;
	return *this;
}

Vector2 operator+(Vector2& left, Vector2& right)
{
	Vector2 output = left;
	output.x += right.x;
	output.y += right.y;
	return output;
}

Vector2 operator-(Vector2& left, Vector2& right)
{
	Vector2 output = left;
	output.x -= right.x;
	output.y -= right.y;
	return output;
}

Vector2 operator*(Vector2& left, float right)
{
	Vector2 output = left;
	output.x *= right;
	output.y *= right;
	return output;
}

Vector2 operator*(float left, Vector2& right)
{
	return operator*(right, left);
}

Vector2 operator/(Vector2& left, float right)
{
	Vector2 output = left;
	output.x /= right;
	output.y /= right;
	return output;
}

bool operator==(Vector2& left, Vector2& right)
{
	return (left.x == right.x) && (left.y == right.y);
}

bool operator!=(Vector2& left, Vector2& right)
{
	return !(left == right);
}