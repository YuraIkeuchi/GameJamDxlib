#include "Vector3.h"
#include <cmath>
//#include <DxLib.h>

Vector3::Vector3() :
	Vector3(0, 0, 0)
{
}

Vector3::Vector3(float x, float y, float z) :
	VECTOR{ x,y,z }
{
}

float Vector3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

Vector3& Vector3::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return *this;
}

float Vector3::dot(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3& v) const
{
	return Vector3(y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}


Vector3 Vector3::operator+() const
{
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

const Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp += v2;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp -= v2;
}

const Vector3 operator*(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp *= s;
}

const Vector3 operator*(float s, const Vector3& v)
{
	return v * s;
}

const Vector3 operator/(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp /= s;
}

const Vector3 lerp(const Vector3& strat, const Vector3& end, const float t) {
	return strat * (1.0f - t) + end * t;
}

const Vector3 easeIn(const Vector3& strat, const Vector3& end, const float t)
{
	float y = t * t;
	return strat * (1.0f - y) + end * y;		;
}

const Vector3 easeOut(const Vector3& strat, const Vector3& end, const float t)
{
	float y = t * (2 - t);
	return strat * (1.0f - y) + end * y;
}

const Vector3 easeInOut(const Vector3& strat, const Vector3& end, const float t)
{
	float y = t * t * (3 - 2 * t);
	return strat * (1.0f - y) + end * y;
}
