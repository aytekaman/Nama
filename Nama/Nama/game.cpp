#include "game.h"

Game::Game()
{
	m_name = string( "Game" );
	m_deltaTime = 0;
    m_sleepInterval = 0.01;
	m_scriptsFolder = string( "GameData/Scripts/" );

	m_activeScene = NULL;

	glfwInit();
	glfwOpenWindow( 800, 600, 8, 8, 8, 8, 0, 0, GLFW_WINDOW );
	glfwSetWindowTitle( m_name.c_str() );

	physics = Physics::GetInstance();
	textureManager = TextureManager::GetInstance();
}

Game::~Game()
{
}

Game* Game::GetInstance()
{
	if( game == NULL )
		game = new Game();

	return game;
}

void Game::LoadScene( string sceneName )
{
	Renderer::GetInstance()->UnregisterAllComponents();
	Physics::GetInstance()->UnregisterAllComponents();

	m_activeScene = new Scene();
	m_activeScene->LoadScript( m_scriptsFolder + sceneName );
}

void Game::Run()
{
	double frameStartTime, frameEndTime; 
	double pStart, pEnd;

	while( true )
	{
		if( glfwGetKey( GLFW_KEY_ESC ) )
			glfwCloseWindow();

		frameStartTime = glfwGetTime();

		if( m_activeScene )
			m_activeScene->Update();
		else
			cout << "No Scene is Loaded." << endl;

		pStart = glfwGetTime();
		Physics::GetInstance()->Update();

		Renderer::GetInstance()->Render();

		glfwSwapBuffers();

		glfwSleep( m_sleepInterval );

		float fps = 1 / m_deltaTime;

		//cout << "FPS: " <<  fps << endl;

		if( fps < 120 )
			m_sleepInterval -= 0.001;
		else if( fps > 180 )
			m_sleepInterval += 0.0001;

		frameEndTime = glfwGetTime();

		m_deltaTime = frameEndTime - frameStartTime;
	}
}

//void Game::addGameObject( GameObject*& g )
//{
//	gameObjects->push_back( g );
//}
//
//void Game::removeGameObject( GameObject*& g )
//{
//	willBeDeleted->push( g );
//
//	//vector<GameObject*>::iterator it = gameObjects->begin();
//
//	//while(  it != Game::gameObjects->end() )
//	//{
//	//	if( *it == gameObject )
//	//	{
//	//		it = gameObjects->erase( it );
//	//		delete gameObject;
//	//	}
//	//	else
//	//		++it;
//	//}
//}

//vector<GameObject*>* Game::getGameObjects()
//{
//	return gameObjects;
//}
//

void Game::PrintMessage( string message )
{
	cout << message << endl;
}

//vector<GameObject*>* Game::gameObjects = NULL;
//queue<GameObject*>* Game::willBeDeleted = NULL;
//GameObject* Game::gameObject = NULL;

Game* Game::game = NULL;