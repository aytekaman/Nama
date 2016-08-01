#include "transform.h"

Transform::Transform()
{
	m_left = Vector3( 1, 0, 0 );
	m_up = Vector3( 0, 1, 0 );
	m_forward = Vector3( 0, 0, 1 );

	m_position = Vector3( 0, 0, 0 );
	m_rotation = Vector3( 0, 0, 0 );
	m_scale = Vector3( 1, 1, 1 );

	calculateTransformationMatrix();
}

Transform::~Transform()
{
}

void Transform::calculateTransformationMatrix()
{
	Matrix4 t;
	t.data[12] = m_position.x;
	t.data[13] = m_position.y;
	t.data[14] = m_position.z;

	Matrix4 ry;
	float deg = m_rotation.y * 0.0174532925;

	ry.data[0] = cos(deg);
	ry.data[10] = cos(deg);
	ry.data[2] = -sin(deg);
	ry.data[8] = sin(deg);

	Matrix4 rx;
	deg = m_rotation.x * 0.0174532925;

	rx.data[5] = cos(deg);
	rx.data[10] = cos(deg);
	rx.data[6] = sin(deg);
	rx.data[9] =-sin(deg);

	Matrix4 rz;
	deg = m_rotation.z * 0.0174532925;

	rz.data[0] = cos(deg);
	rz.data[5] = cos(deg);
	rz.data[4] = -sin(deg);
	rz.data[1] = sin(deg);

	m_transformationMatrix = t * ry * rx * rz;

	m_forward = ry * rx * rz * Vector3(0,0,1);
	m_left = ry * rx * rz * Vector3(1,0,0);
	m_up = Vector3::Cross( m_forward, m_left );

	m_forward.normalize();
	m_left.normalize();
	m_up.normalize();
}

void Transform::Rotate( float angle, int axis, ReferenceFrame referenceFrame )
{
	if( axis == 0 )
	{
		Matrix4 rx;
		float deg = angle * 0.0174532925;

		rx.data[5] = cos(deg);
		rx.data[10] = cos(deg);
		rx.data[6] = sin(deg);
		rx.data[9] =-sin(deg);

		m_transformationMatrix = m_transformationMatrix * rx;
		m_forward = rx * m_forward;
		m_left = rx * m_left;
	}
	else if( axis == 1 )
	{
		Matrix4 ry;
		float deg = angle * 0.0174532925;

		ry.data[0] = cos(deg);
		ry.data[10] = cos(deg);
		ry.data[2] = -sin(deg);
		ry.data[8] = sin(deg);

		m_transformationMatrix = m_transformationMatrix * ry;
		m_forward = ry * m_forward;
		m_left = ry * m_left;
	}
	else if( axis == 2 )
	{
		Matrix4 rz;
		float deg = angle * 0.0174532925;

		rz.data[0] = cos(deg);
		rz.data[5] = cos(deg);
		rz.data[4] = sin(deg);
		rz.data[1] =-sin(deg);

		m_transformationMatrix = m_transformationMatrix * rz;
		m_forward = rz * m_forward;
		m_left = rz * m_left;
	}

	m_rotation.x = (-atan2(m_transformationMatrix.data[9],m_transformationMatrix.data[10]) / 3.14159265) * 180;
	m_rotation.y = (asin(m_transformationMatrix.data[8]) / 3.14159265) * 180;
	m_rotation.z = (-atan2(m_transformationMatrix.data[4],m_transformationMatrix.data[0]) / 3.14159265) * 180;

	m_up = Vector3::Cross(m_forward, m_left);

	m_up.normalize();
	m_forward.normalize();
	m_left.normalize();
}

void Transform::setPosition( float x, float y, float z )
{
	m_position = Vector3( x, y, z );
	calculateTransformationMatrix();
}

void Transform::setPosition( Vector3 position )
{
	m_position = position;
	calculateTransformationMatrix();
}

void Transform::setRotation( float x, float y, float z )
{
	m_rotation = Vector3( x, y, z );
	calculateTransformationMatrix();
}

void Transform::setRotation( Vector3 rotation )
{
	m_rotation = rotation;
	calculateTransformationMatrix();
}

void Transform::setScale( float x, float y, float z )
{
	m_scale = Vector3( x, y, z );
}

void Transform::setScale( Vector3 scale )
{
	m_scale = scale;
}

void Transform::Translate( float x, float y, float z, ReferenceFrame referenceFrame )
{
	Matrix4 t;
	t.data[12] = x;
	t.data[13] = y;
	t.data[14] = z;

	m_transformationMatrix = m_transformationMatrix * t;

	m_position = m_transformationMatrix * Vector3(0,0,0);
}