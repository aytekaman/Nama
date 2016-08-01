#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "vector3.h"
#include "..\include\GL\glfw.h"

class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	float operator[]( int i ){ return data[i]; }
	Matrix4 operator*( Matrix4 &other );
	Vector3 Matrix4::operator*( Vector3 &vector );
	Matrix4 GetInverse();
	float GetDeterminant();

	// Returns GL compatible matrix, which has a type of GLfloat[16].
	inline GLfloat* GetGLMatrix(){ return (GLfloat*)data; }

private:
	float data[16];

	// TODO
	static Matrix4 Identity;

	friend class Transform;
};

#endif