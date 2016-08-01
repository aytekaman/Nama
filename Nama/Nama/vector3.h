#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <math.h>

class Vector3
{
public:
	Vector3();
	~Vector3();
	Vector3(float x, float y, float z);
	void normalize();
	float getLength();
	float getSquaredLength();
	Vector3 operator+(Vector3 &a);
	Vector3 operator+=(float a);
	Vector3 operator+=(Vector3 &other);
	Vector3 operator-(Vector3 &a);
	Vector3 operator*(float s);
	static Vector3 Lerp(Vector3 a, Vector3 b, float t);
	static float Dot(Vector3 a, Vector3 b);
	static Vector3 Cross(Vector3 a, Vector3 b);

	float x, y, z;
};

Vector3 operator*(float s, Vector3 a);


#endif