#ifndef _COMPONENTMANAGER_H_
#define _COMPONENTMANAGER_H_

#include "component.h"

class IComponentManager
{
protected:
	IComponentManager(){};
	~IComponentManager(){};

	virtual void RegisterComponent( Component* component ) = 0;
	virtual void UnregisterComponent( Component* component ) = 0;

	virtual void UnregisterAllComponents() = 0;
};

#endif