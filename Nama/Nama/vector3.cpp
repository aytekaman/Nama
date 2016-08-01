#include "Vector3.h"

Vector3::Vector3()
{
	x = y = z = 0;
}

Vector3::~Vector3()
{
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void Vector3::normalize()
{
	float length = getLength();
	x /= length;
	y /= length;
	z /= length;
}

float Vector3::getLength()
{
	return sqrt(x*x + y*y + z*z);
}

float Vector3::getSquaredLength()
{
	return x*x + y*y + z*z;
}

Vector3 Vector3::operator+(Vector3 &a)
{
	return Vector3(x+a.x, y+a.y, z+a.z);
}

Vector3 Vector3::operator+=(float a)
{
	this->x += a;
	this->y += a;
	this->z += a;
	return *this;
}

Vector3 Vector3::operator+=(Vector3 &other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vector3 Vector3::operator-(Vector3 &a)
{
	return Vector3(x - a.x, y - a.y, z - a.z);
}

Vector3 Vector3::operator*(float s)
{
	return Vector3(x*s, y*s, z*s);
}

Vector3 operator*(float s, Vector3 a)
{
	return Vector3(a.x*s, a.y*s, a.z*s);
}

Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float t)
{
	return Vector3(a*(1-t) + b*t);
}

float Vector3::Dot(Vector3 a, Vector3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::Cross(Vector3 a, Vector3 b)
{
	return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

