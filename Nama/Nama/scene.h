#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>
#include <vector>

#include "script.h"

using namespace std;

class Scene
{
public:
	Scene();
	~Scene();

	// Meh.
	void LoadScript( string scriptName );

	void AddGameObject( GameObject*& gameObject );
	void RemoveGameObject( GameObject*& gameObject );

	void Update();

	// Will unregister all components of its GameObjects
	void Unload();

	vector<GameObject*>* GetGameObjects(){ return gameObjects; }
	Script* GetScript(){ return m_script; }

private:
	string m_name;
	Script* m_script;
	vector<GameObject*> *gameObjects;
};

#endif