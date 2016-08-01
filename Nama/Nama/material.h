#ifndef _MATERIAL_H_
#define _MATERIAL_H

#include <string>

#include "vector3.h"
#include "texture.h"
#include "textureManager.h"

using namespace std;

class Material
{
public:
	Material()
	{
		m_texture = NULL;
		// SetTexture( "Skeleton.tga" );
		SetDiffuseColor( Vector3( float(rand())/RAND_MAX,float(rand())/RAND_MAX,float(rand())/RAND_MAX ) );
		SetDiffuseColor( Vector3( 1,1,1) );
	}

	~Material();

	Vector3 GetDiffuseColor(){ return m_diffuseColor; }
	float GetAttribute( string* attributeName );

	void SetDiffuseColor( Vector3 &diffuseColor ){ m_diffuseColor = diffuseColor; }
	void SetAttribute( string* attributeName, float value );
	
	void SetTexture( string textureName )
	{
		m_texture = TextureManager::GetInstance()->GetTexture( textureName );
	}

private:
	// Named attributes might be better for generic implementation
	Vector3 m_diffuseColor;
	Texture* m_texture;

	friend class Renderer;
};

#endif