#ifndef PHYS_H
#define PHYS_H

struct Vector2
{
	Vector2();

	float x, y;

	Vector2 normal();
	void normalize();

	float length();

	// Operator Overload
	Vector2& operator=(Vector2& right);

	Vector2& operator+=(Vector2& right);
	Vector2& operator-=(Vector2& right);
	Vector2& operator*=(float right);
};

struct SteeringOutput
{
	Vector2 linear;
	float angular;
};

// Operator Overloads
Vector2 operator+(Vector2& left, Vector2& right);
Vector2 operator-(Vector2& left, Vector2& right);

Vector2 operator*(Vector2& left, float right);
Vector2 operator*(float left, Vector2& right);

Vector2 operator/(Vector2& left, float right);

#endif