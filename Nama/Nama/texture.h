#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
//#include "textureManager.h"
//#include "renderer.h"

using namespace std;

class Texture
{
private:
	Texture(){};
	~Texture();

	string* m_name;
	int m_id;

	friend class TextureManager;
	friend class Renderer;
};

#endif _TEXTURE_H_