#include "gameObject.h"
#include "game.h"

GameObject::GameObject()
{
	m_ID = ++lastGivenID;

	m_name = new string( "GameObject" );

	m_script = NULL;

	m_transform = new Transform();

	Mesh *m = new Mesh();

	AddMesh( m );
}

GameObject::~GameObject()
{
	if( m_script != NULL )
	{
		delete m_script;
		//m_script = NULL;
	}

	Renderer::GetInstance()->UnregisterComponent( m_mesh );
	Physics::GetInstance()->UnregisterCollider( m_collider );

	delete m_transform;
	delete m_name;
}

GameObject* GameObject::Create()
{
	GameObject *gameObject = new GameObject();

	Game::GetInstance()->GetActiveScene()->AddGameObject( gameObject );

	return gameObject;
}

void GameObject::Destroy( GameObject*& gameObject )
{
	Game::GetInstance()->GetActiveScene()->RemoveGameObject( gameObject );
}

void GameObject::VDraw()
{

}

void GameObject::VUpdate()
{
}

void GameObject::AddCamera()
{
	m_camera = new Camera();

	GameObject *thisGameObject = this;

	m_camera->SetGameObject( thisGameObject );

	Renderer::GetInstance()->RegisterComponent( m_camera );
}

void GameObject::AddCollider( Collider*& collider )
{
	m_collider = collider;

	GameObject *thisGameObject = this;

	collider->SetGameObject( thisGameObject );

	Physics::GetInstance()->RegisterCollider( collider, m_ID );
}

void GameObject::AddCollider( float w, float h, int layerIndex )
{
	m_collider = new Collider( w, h );

	GameObject *thisGameObject = this;

	m_collider->SetGameObject( thisGameObject );

	Physics::GetInstance()->RegisterCollider( m_collider, layerIndex );

	m_collider->p_position = &this->m_transform->m_position;
}

void GameObject::RemoveCollider()
{
	Physics::GetInstance()->UnregisterCollider( m_collider );
}

void GameObject::AddMesh( Mesh*& mesh )
{
	m_mesh = mesh;

	GameObject *thisGameObject = this;

	mesh->SetGameObject( thisGameObject );

	Renderer::GetInstance()->RegisterComponent( mesh );
}

void GameObject::AddScript( string fileName )
{
	if( m_script == NULL )
		m_script = new Script( fileName.c_str() );

	GameObject *thisGameObject = this;

	m_script->SetGameObject( thisGameObject );

	// Exception
}

void GameObject::UnregisterComponents()
{
}

int GameObject::lastGivenID = -1;