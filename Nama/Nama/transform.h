#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "component.h"
#include "vector3.h"
#include "matrix4.h"

enum ReferenceFrame
{
	Local,
	World
};

class Transform : public Component
{
public:
	Transform();
	~Transform();

	Vector3 getPosition(){ return m_position; }
	Vector3 getRotation(){ return m_rotation; }
	Vector3 getScale(){ return m_scale; }


	void Rotate( float angle, int axis, ReferenceFrame referenceFrame = ReferenceFrame::Local );
	void Rotate( float x, float y, float z, ReferenceFrame referenceFrame = ReferenceFrame::Local );
	void Rotate( float angle, Vector3 rotationAxis, ReferenceFrame referenceFrame = ReferenceFrame::Local ); 

	void Translate( float x, float y, float z, ReferenceFrame referenceFrame = ReferenceFrame::Local );
	void Translate( Vector3 translationVector, ReferenceFrame referenceFrame = ReferenceFrame::Local );

	void setPosition( float x, float y, float z );
	void setPosition( Vector3 position );
	void setRotation( float x, float y, float z );
	void setRotation( Vector3 rotation );
	void setScale( float x, float y, float z );
	void setScale( Vector3 scale );

private:
	void calculateTransformationMatrix();

	Matrix4 m_transformationMatrix;

	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;

	Vector3 m_left;
	Vector3 m_up;
	Vector3 m_forward;

	friend class Renderer;
	friend class Physics;
	friend class GameObject;
};

#endif