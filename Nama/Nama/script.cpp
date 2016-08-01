#include "script.h"

#include "luaGameObject.h"
#include "tolua++.h"

Script::Script( string name )
{
	m_name = name;

	L = lua_open();

	luaL_openlibs( L );

	tolua_luaGameObject_open ( L );

	luaL_dofile( L, m_name.c_str() );

	std::cout << "Script: " << name << std::endl;
}

Script::~Script()
{
	 //if( L != NULL )
		//lua_close( L );
}

void Script::SendUpdateMessage( float deltaTime )
{
	// Note: If function calls can't find appropriate function on the script, 
	// an error value will be pushed onto the stack will cause memory leak.
	// Should handle this soon.
	lua_getglobal( L, "OnUpdate" );

	tolua_pushnumber( L , deltaTime );

	lua_pcall( L, 1, 0, 0 );

	// Sample call fro user defined types. toLua++ handles actual type recognition stuff
	// lua_getglobal( L, "AfterUpdate" );
	// tolua_pushusertype( L ,GetGameObject(), "GameObject");
	// lua_pus (L, GetGameObject() );
	// lua_pcall(L, 1, 0, 0);
}

void Script::SendCollisionMessage( string name, int id1, int id2 )
{
	lua_getglobal( L, name.c_str() );

	tolua_pushnumber( L , id1 );
	tolua_pushnumber( L , id2 );

	lua_pcall( L, 2, 0, 0 );
}