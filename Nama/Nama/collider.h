#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "component.h"
#include "vector3.h"

class Collider : public Component
{
public:
	Collider( float width = 10, float height = 10 );
	~Collider();

	float inline GetLayerIndex(){ return m_layerIndex; }
	float inline GetRadius(){ return m_radius; }

	void SetLayerIndex( int layerIndex );
	void SetRadius( float radius ); 

	Vector3* p_position;

private:
	float m_radius;

	float m_width, m_height;

	

	// Only the colliders with the same layerIndex may collide
	float m_layerIndex;

	// Used to calculate continuous collisions
	Vector3 previousPosition;

	friend class Physics;
};

#endif