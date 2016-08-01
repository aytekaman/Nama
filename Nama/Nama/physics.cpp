#include "physics.h"

Physics::Physics()
{
	colliders = new vector<Collider*>();

	colliderLayers = new map<int, vector<Collider*>*>();

	colliderLayersIndices = new vector<CollidingPair>();

	cout << "Physics have been initialized." << endl;
}

Physics::~Physics()
{
}

void Physics::EnableCollisionLayers( string name, int layer1, int layer2 )
{
	CollidingPair p;

	p.firstLayer = layer1;
	p.secondLayer = layer2;
	p.name = name;

	Physics::GetInstance()->colliderLayersIndices->push_back( p );
}

Physics* Physics::GetInstance()
{
	if( physics == NULL )
		physics = new Physics();

	return physics;
}

void Physics::Update()
{
	for( int i = 0; i < colliderLayersIndices->size(); i++ )
	{
		// cout << i << endl;

		CollidingPair p = colliderLayersIndices->at( i );

		vector<Collider*> *layer1, *layer2;

		map< int, vector<Collider*>*>::iterator it = colliderLayers->find( p.firstLayer );

		if( it != colliderLayers->end() )
		{
			layer1 = it->second;

			// cout << "L1: " << layer1->size() << endl;

			it = colliderLayers->find( p.secondLayer );

			// sort layers!, if a layer contains no element at all, waste of CPU
			if( it != colliderLayers->end() )
			{
				layer2 = it->second;

				// cout << "L2: " << layer2->size() << endl;
				// Layers found, do calculations

				Collider *collider, *otherCollider;

				for( int j = 0; j < layer1->size(); ++j )
				{
					collider = layer1->at( j );

					for( int k = 0; k < layer2->size(); ++k )
					{
						otherCollider = layer2->at( k );

						Vector3 delt = *collider->p_position - *otherCollider->p_position;

						//Vector3 delt = collider->m_gameObject->m_transform->m_position - otherCollider->m_gameObject->m_transform->m_position;
						//if( delt.getLength() < collider->m_radius + otherCollider->m_radius )
						//{
							//Game::getGameObjects()->at( 0 )->GetScript()->Col( p.name, collider->m_gameObject->m_ID, otherCollider->m_gameObject->m_ID );
							// cout << "Colliding " << p.name <<  collider->m_gameObject->m_ID << " and " << otherCollider->m_gameObject->m_ID << endl;
						//}

						if ( abs( delt.x ) < collider->m_width/2 + otherCollider->m_width/2 )
						{
							if ( abs( delt.y ) < collider->m_height/2 + otherCollider->m_height/2 )
							{
								Game::GetInstance()->GetActiveScene()->GetScript()->SendCollisionMessage( p.name, collider->m_gameObject->m_ID, otherCollider->m_gameObject->m_ID );
							}
						}
					}
				}
			}
		}
	}
}

void Physics::RegisterCollider( Collider*& collider, int index )
{
	if( colliderLayers->find( index ) == colliderLayers->end() )
	{
		vector<Collider*> *currentLayer = new vector<Collider*>();

		colliderLayers->insert( pair<int, vector<Collider*>*>( index, currentLayer ) );

		currentLayer->push_back( collider );

		cout << "New layer is created" << endl;
	}
	else
	{
		map< int, vector<Collider*>*>::iterator it = colliderLayers->find( index );

		it->second->push_back( collider );
	}

	// colliders->push_back( collider );
}

void Physics::UnregisterCollider( Collider*& collider )
{
	//cout << "unregistering collider" << endl;

	map<int, vector<Collider*>*>::iterator it = colliderLayers->begin();

	while( it != colliderLayers->end() )
	{
		vector<Collider*> *currentLayer = it->second;

		vector<Collider*>::iterator it2 = currentLayer->begin();

		while(  it2 != currentLayer->end() )
		{
			if( *it2 == collider )
			{
				it2 = currentLayer->erase( it2 );
			}
			else
				++it2;
		}

		++it;
	}
}

void Physics::UnregisterAllComponents()
{
	colliderLayers->clear();

	//for( map<int, vector<Collider*>*>::iterator it = colliderLayers->begin(); it != colliderLayers->end(); ++it )
	//{
	//	(*it).second->erase();
	//}
}

Physics* Physics::physics = NULL;