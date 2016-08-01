#include "textureManager.h"

TextureManager::TextureManager()
{
	textures = new vector<Texture*>();
	cout << "Texture Manager have been initialized." << endl;
}

TextureManager::~TextureManager()
{
}

TextureManager* TextureManager::GetInstance()
{
	if( textureManager == NULL )
		textureManager = new TextureManager();

	return textureManager;
}

Texture* TextureManager::GetTexture( string textureName )
{
	for( int i = 0; i < textures->size(); i++ )
	{
		if( !textures->at( i )->m_name->compare( textureName ) )
		{ 
			return textures->at( i );
		}
	}

	GLuint id;

	glGenTextures( 1, &id );
	glBindTexture(  GL_TEXTURE_2D, id );

	glfwLoadTexture2D( textureName.c_str(), GLFW_BUILD_MIPMAPS_BIT );
	
	// Default filtering parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	Texture *texture = new Texture();
	texture->m_id = id;
	texture->m_name = new string( textureName ); // Hating those string stuff, might change to boost::string...

	textures->push_back( texture );
	
	cout << "Created a texture using: " << textureName << endl;

	return texture;
}

TextureManager* TextureManager::textureManager = NULL;