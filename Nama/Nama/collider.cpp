#include "collider.h"

Collider::Collider( float width, float height )
{
	// m_radius = radius;
	m_width = width;
	m_height = height;
}

Collider::~Collider()
{
}

void Collider::SetLayerIndex( int index )
{
}

void Collider::SetRadius( float radius )
{
	m_radius = radius;
}