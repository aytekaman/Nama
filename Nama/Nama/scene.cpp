#include "scene.h"	
#include "gameObject.h"

Scene::Scene()
{
	gameObjects = new vector<GameObject*>();


}

Scene::~Scene()
{
}

void Scene::LoadScript( string scriptName )
{
	m_script = new Script( scriptName );

	//GameObject *camera = GameObject::Create();
	//camera->AddCamera();

	//camera->GetTransform()->Rotate(180,1);
	//camera->GetTransform()->setPosition( 300, 200, 400 );
}

void Scene::AddGameObject( GameObject*& gameObject )
{
	gameObjects->push_back( gameObject );
}

void Scene::RemoveGameObject( GameObject*& gameObject )
{
	vector<GameObject*>::iterator it = gameObjects->begin();

	// One object shouldn't inserted into a list twice, so should break after one deletion. 
	while(  it != gameObjects->end() )
	{
		if( *it == gameObject )
		{
			it = gameObjects->erase( it );
			delete gameObject;
		}
		else
			++it;
	}
}

void Scene::Update()
{
	m_script->SendUpdateMessage( Game::GetInstance()->GetDeltaTime() );

	for( vector<GameObject*>::iterator it = gameObjects->begin(); it != gameObjects->end(); ++it )
	{
		(*it)->VUpdate();
	}
}

// Will unregister all components of its GameObjects
void Scene::Unload()
{
	for( vector<GameObject*>::iterator it = gameObjects->begin(); it != gameObjects->end(); ++it )
	{
	}
}