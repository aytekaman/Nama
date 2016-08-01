#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>
#include <string>
#include <vector>

#include "..\include\GL\glfw.h"

#include "game.h"
#include "IComponentManager.h"

using namespace std;

class Renderer : public IComponentManager
{
public:
	void Render();

	static Renderer* GetInstance();

	// IComponentManager Interface members
	void RegisterComponent( Component* component );
	void UnregisterComponent( Component* Component );
	void UnregisterAllComponents(){ m_meshes->clear(); }

protected:
	Renderer();
	~Renderer();

private:
	// Make a parent class like RenderableComponent for meshes, particles, gui elements etc
	vector<Mesh*> *m_meshes;
	Camera *m_activeCamera;

	// vector<ParticleSystem*>
	// vector<GUIElement*>

	static Renderer* renderer;
};

#endif