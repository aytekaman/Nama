#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <string>

#include "camera.h"
#include "collider.h"
#include "mesh.h"
#include "script.h"
#include "transform.h"
#include "vector3.h"

#include "renderer.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void VUpdate();
	virtual void VDraw();

	Collider* GetCollider(){ return m_collider; }
	Transform* GetTransform(){ return m_transform; }
	Mesh* GetMesh(){ return m_mesh; }
	Script* GetScript(){ return m_script; }


	string* GetName(){ return m_name; }
	int GetID(){ return m_ID; }

	void setName( string* name );

	void AddCamera();

	// Sphere Collider
	void AddCollider( float w, float h, int layerIndex );
	void AddCollider( Collider*& collider);
	void RemoveCollider();

	void AddMesh();
	void AddMesh( Mesh*& mesh );
	void AddScript( string fileName );

	void UnregisterComponents();

	// Static creation functions. Might be good idea to move them in a factory class
	static GameObject* Create();
	static GameObject* CreateAnimatedSprite( string textureName, int width, int height, int verticalTileCount, int horiziontalTileCount );
	static GameObject* CreateSprite( string textureName, int width, int height );

	// Destroys given object, unregisters components from its managers and deletes them
	static void Destroy( GameObject*& gameObject );

private:
	Collider *m_collider;
	Mesh *m_mesh;
	Script *m_script;
	Transform *m_transform;

	// This is somewhat redundat, should make a dedicated child class for camera derived from GameObject 
	Camera *m_camera;

	string *m_name;
	int m_ID;
	static int lastGivenID;

	friend class Physics;
};

#endif