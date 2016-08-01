#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <string>

using namespace std;

#include "component.h"

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

class Script : public Component
{
public:
	Script( string name );
	~Script();

	void SendStartMessage();
	void SendUpdateMessage( float deltaTime );
	void SendCollisionMessage( string name, int gameObjectID, int otherGameObjectID );

private:
	string m_name;
	lua_State *L;
};

#endif