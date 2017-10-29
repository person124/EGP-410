#include "Phys.h"

#include <math.h>

#include "Unit.h"

Vector2 Vector2::toVector(float angle)
{
	return Vector2(cosf(angle), sinf(angle));
}

float Vector2::dot(Vector2& v1, Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
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
	Vector2 output = *this / length();
	return output;
}

void Vector2::normalize()
{
	float len = length();
	x /= len;
	y /= len;
}

float Vector2::length()
{
	return sqrtf(x * x + y * y);
}

float Vector2::toAngle()
{
	return atan2f(y, x);
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

Ray::Ray(Unit* unit)
{
	origin = unit->getPosition();
	x = unit->getVelocity().x;
	y = unit->getVelocity().y;
}

bool isInsideBounds(Vector2& bounds, float num)
{
	return num >= bounds.x && num <= bounds.y;
}

Collision* Wall::checkCollision(Ray& raycast)
{
	Collision* col = NULL;

	float xOffset = min.x;
	float yOffset = min.y;

	Vector2 xBounds = Vector2(min.x - xOffset, max.x - xOffset);
	Vector2 yBounds = Vector2(min.y - yOffset, max.y - yOffset);

	Vector2 rayXBounds;
	if (raycast.origin.x < raycast.origin.x + raycast.x)
	{
		rayXBounds.x = raycast.origin.x;
		rayXBounds.y = raycast.origin.x + raycast.x;
	}
	else
	{
		rayXBounds.y = raycast.origin.x;
		rayXBounds.x = raycast.origin.x + raycast.x;
	}

	Vector2 rayYBounds;
	if (raycast.origin.y < raycast.origin.y + raycast.y)
	{
		rayYBounds.x = raycast.origin.y;
		rayYBounds.y = raycast.origin.y + raycast.y;
	}
	else
	{
		rayYBounds.y = raycast.origin.y;
		rayYBounds.x = raycast.origin.y + raycast.y;
	}

	rayXBounds -= xOffset;
	rayYBounds -= yOffset;

	bool doesCollide = true;
	if (!isInsideBounds(xBounds, rayXBounds.x) && !isInsideBounds(xBounds, rayXBounds.y))
		doesCollide = false;
	if (!doesCollide || (!isInsideBounds(yBounds, rayYBounds.x) && !isInsideBounds(yBounds, rayYBounds.y)))
		doesCollide = false;

	if (doesCollide)
	{
		float p[4] = { -raycast.x, raycast.x, -raycast.y, raycast.y };
		float q[4] = { raycast.origin.x - min.x, max.x - raycast.origin.x, raycast.origin.y - min.y, max.y - raycast.origin.y };
		float col1 = (float)-INT_MAX;

		for (int i = 0; i < 4; i++)
		{
			float t = q[i] / p[i];
			if (p[i] < 0 && col1 < t)
				col1 = t;
		}

		if (col1 > 1 || col1 < 0)
			return col;

		col = new Collision();
		col->position.x = raycast.origin.x + col1 * raycast.x;
		col->position.y = raycast.origin.y + col1 * raycast.y;
		col->normal = getNormalFromPoint(col->position);
	}

	return col;
}

Vector2 Wall::getNormalFromPoint(Vector2& point)
{
	if (point.x == min.x)
		return Vector2(-1, 0);
	if (point.x == max.x)
		return Vector2(1, 0);

	if (point.y == min.y)
		return Vector2(0, -1);
	if (point.y == max.y)
		return Vector2(0, 1);

	return Vector2();
}

bool Wall::isInside(Vector2& pos)
{
	return pos.x >= min.x && pos.x <= max.x && pos.y >= min.y && pos.y <= max.y;
}