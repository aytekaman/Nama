#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <string>
#include <vector>
#include <iostream>

#include <GL\glfw.h>

#include "texture.h"

using namespace std;

class TextureManager
{
protected:
	TextureManager();
	~TextureManager();

public:
	// Singleton
	static TextureManager* GetInstance();

	Texture* GetTexture( const string textureName );

private:
	static TextureManager* textureManager; // Singleton instance
	vector<Texture*> *textures;
};

#endif