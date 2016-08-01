#include "mesh.h"

void Mesh::SetMaterialTexture( string textureName )
{
	m_material->SetTexture( textureName );
}

void Mesh::SetMaterialColor( float r, float g, float b, float a )
{
	m_material->SetDiffuseColor( Vector3( r, g, b) );
}

void Mesh::SetUVAnimation( int horizontalTileCount, int verticalTileCount )
{
	m_horizontalTileCount = horizontalTileCount;
	m_verticalTileCount = verticalTileCount;
}

void Mesh::StartUVAnimation()
{
	m_isPlaying = true;
}

void Mesh::StopUVAnimation()
{
	m_isPlaying = false;
}

void Mesh::SetUVAnimationTime( float animationTime )
{
	// TODO: clamp to 0:1
	m_animationTime = animationTime;
}

void Mesh::CreateUVAnimationClip( string name, int startFrame, int endFrame, int mode )
{
	UVAnimationClip *clip = new UVAnimationClip();
	clip->m_startFrame = startFrame;
	clip->m_endFrame = endFrame;
	clip->clipName = name;
	clip->mode = mode;

	animationClips->push_back( clip );
}

void Mesh::SetUVAnimationClip( string clipName )
{
	for( int i = 0; i < animationClips->size(); ++i )
	{
		if( animationClips->at( i )->clipName.compare( clipName ) == 0 )
		{
			m_activeUVAnimationClip = animationClips->at( i );
			// m_animationTime = 0;
			return;
		}
	}

	cout << "Animation clip \"" << clipName << "\" not found." << endl; 
}

void Mesh::SetUVAnimationSpeed( float speed )
{
	m_animationSpeed = speed;
}