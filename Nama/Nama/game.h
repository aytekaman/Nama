#ifndef _GAME_H_
#define _GAME_H_

#include <iterator>
#include <vector>
#include <queue>
#include <string>

#include <iostream>

#include "..\include\GL\glfw.h"

#include "gameObject.h"
#include "input.h"
#include "physics.h"
#include "renderer.h"
#include "scene.h"
#include "textureManager.h"

using namespace std;

class Game
{
public:
	static Game* GetInstance(); 

	void Run();
	vector<GameObject*>* GetGameObjects();
		
	// sceneName will be used to initialize the script with the same name
	void LoadScene( string sceneName );

	void AddScene( Scene*& scene );
	void RemoveScene( Scene*& scene );
	void SetActiveScene( Scene*& scene );
	
	void PrintMessage( string message );

	void SetName( string name );

	Scene* GetActiveScene(){ return m_activeScene; }
	string GetName(){ return m_name; }
	double GetDeltaTime(){ return m_deltaTime; }
	string GetScriptsFolder() { return m_scriptsFolder; }
	
protected:
	Game();
	~Game();

private:
	static Game* game;

	string m_name;
	string m_scriptsFolder; // = "GameData/Scripts/";
	int m_minFrameRate, m_maxFrameRate;
	double m_deltaTime, m_sleepInterval;

	// ComponentManagers
	Physics* physics;
	TextureManager* textureManager;

	Scene* m_activeScene;
	vector<Scene*> *scenes;
};

#endif