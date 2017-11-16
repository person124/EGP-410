#ifndef VECTOR_2_H
#define VECTOR_2_H

struct Vector2
{
	static Vector2 toVector(float angle);
	static float dot(Vector2& v1, Vector2& v2);

	Vector2();
	Vector2(float xVal, float yVal);

	Vector2 normal();
	void normalize();

	float length();

	//Variables
	float x, y;

	// Operator Overload
	Vector2& operator=(Vector2& right);

	Vector2& operator+=(Vector2& right);
	Vector2& operator-=(Vector2& right);
	Vector2& operator+=(float right);
	Vector2& operator-=(float right);
	Vector2& operator*=(float right);
	Vector2& operator/=(float right);
};

// Operator Overloads
Vector2 operator+(Vector2& left, Vector2& right);
Vector2 operator-(Vector2& left, Vector2& right);

Vector2 operator*(Vector2& left, float right);
Vector2 operator*(float left, Vector2& right);

Vector2 operator/(Vector2& left, float right);

bool operator==(Vector2& left, Vector2& right);
bool operator!=(Vector2& left, Vector2& right);

#endif