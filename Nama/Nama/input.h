#include "..\include\GL\glfw.h"
#include "vector3.h"

class Input
{
public:
	Input();
	static bool GetKey( char key );
	static Vector3* GetMousePosition();
	static bool GetMouseButton( int buttonNo );
};