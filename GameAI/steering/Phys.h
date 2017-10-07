#ifndef PHYS_H
#define PHYS_H

struct Vector2
{
	//Static Functions
	static Vector2 toVector(float angle);

	Vector2();
    Vector2(float xVal, float yVal);

	float x, y;

	Vector2 normal();
	void normalize();

	float length();

	// Operator Overload
	Vector2& operator=(Vector2& right);

	Vector2& operator+=(Vector2& right);
	Vector2& operator-=(Vector2& right);
	Vector2& operator*=(float right);
    Vector2& operator/=(float right);
};

// Operator Overloads
Vector2 operator+(Vector2& left, Vector2& right);
Vector2 operator-(Vector2& left, Vector2& right);

Vector2 operator*(Vector2& left, float right);
Vector2 operator*(float left, Vector2& right);

Vector2 operator/(Vector2& left, float right);


struct SteeringOutput
{
	Vector2 linear;
	float angular = 0;
};

struct WeightedBehaviour
{
    WeightedBehaviour(SteeringOutput steer, float w)
    {
        steering = steer;
        weight = w;
    };
    SteeringOutput steering;
    float weight;
};

typedef WeightedBehaviour WeightB;

#endif