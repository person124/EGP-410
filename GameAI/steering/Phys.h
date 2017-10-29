#ifndef PHYS_H
#define PHYS_H

#include "Trackable.h"

class Unit;

//Vectors and rays
struct Vector2
{
	//Static Functions
	static Vector2 toVector(float angle);
	static float dot(Vector2& v1, Vector2& v2);

	Vector2();
    Vector2(float xVal, float yVal);

	float x, y;

	Vector2 normal();
	void normalize();

	float length();

	float toAngle();

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

struct Ray : public Vector2
{
	Ray() {};
	Ray(Unit* unit);
	//x and y are its direction
	Vector2 origin;
};


//Steering Related Stuff
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


//Walls
struct Collision : public Trackable
{
	Vector2 position;
	Vector2 normal;
};

struct Wall : public Trackable
{
	Wall() {};
	Wall(float minX, float minY, float maxX, float maxY)
	{
		min = Vector2(minX, minY);
		max = Vector2(maxX, maxY);
	}
	Vector2 min;
	Vector2 max;

	Collision* checkCollision(Ray& raycast);
	Vector2 getNormalFromPoint(Vector2& point);
	bool isInside(Vector2& pos);
};

#endif