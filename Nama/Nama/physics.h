#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <vector>
#include <map>
#include <iterator>
#include <iostream> // to be deleted
#include <string>

#include "collider.h"
#include "gameObject.h"

using namespace std;

class Physics
{
protected:
	Physics();
	~Physics();

public:
	// Singleton
	static Physics* GetInstance();

	static void EnableCollisionLayers( string name, int index1, int index2 );

	void Update();
	void RegisterCollider( Collider*& collider, int index );

	void UnregisterColliderFromLayer( Collider*& collider, int index );
	void UnregisterCollider( Collider*& collider );

	void UnregisterAllComponents();

private:
	static Physics* physics; // Singleton instance
	vector<Collider*> *colliders;

	struct CollidingPair
	{
		string name;
		int firstLayer;
		int secondLayer;
	};

	vector<CollidingPair> *colliderLayersIndices;
	map<int, vector<Collider*>*> *colliderLayers;
};

#endif