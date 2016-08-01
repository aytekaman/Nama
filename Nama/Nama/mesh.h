#ifndef _MESH_H_
#define _MESH_H_

#include <vector>

#include "component.h"
#include "vector3.h"
#include "material.h"

using namespace std;

class Mesh : public Component
{
public:
	Mesh() : Component()
	{
		m_material = new Material();

		animationClips = new vector<UVAnimationClip*>();

		m_isPlaying  = false;
		m_animationSpeed = 1;
		m_animationTime = 0;

		SetUVAnimation( 1, 1 );

		m_activeUVAnimationClip = NULL;

	}

	Material* GetMaterial(){ return m_material; }

	void SetMaterialTexture( string textureName );
	void SetMaterialColor( float r, float g, float b, float a );

	void SetUVAnimation( int horizontalTileCount, int verticalTileCount );
	void SetUVAnimationTime( float animationTime );
	void SetUVAnimationSpeed( float speed );

	// 
	struct UVAnimationClip
	{
		string clipName;
		int m_startFrame;
		int m_endFrame;
		int m_time; // Between 0:1 ( start:end )
		int mode; // Put an enumeration here ( Repeat, ping-pong, once etc... ) 
	};

	vector<UVAnimationClip*>* animationClips;

	// start and end frames are exclusive
	void CreateUVAnimationClip( string clipName, int startFrame, int endFrame, int mode );
	void SetUVAnimationClip( string clipName );



	void StartUVAnimation();
	void StopUVAnimation();

private:
	Material *m_material;

	Vector3* m_vertices;
	Vector3* m_normals;
	Vector3* m_UVs;
	Vector3* m_UV2s;

	UVAnimationClip* m_activeUVAnimationClip; 

	bool m_isPlaying;
	int m_horizontalTileCount, m_verticalTileCount;
	float m_animationSpeed, m_animationTime;

	friend class Renderer;
};

#endif