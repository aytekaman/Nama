#include "input.h"

bool Input::GetKey( char key )
{
	return (bool)glfwGetKey( key );
}

Vector3* Input::GetMousePosition()
{
	int x, y;

	glfwGetMousePos( &x, &y );

	// HACK, use window parameters
	return new Vector3( (float)x, 600.0 - y, 0);
}

bool Input::GetMouseButton( int buttonNo )
{
	return glfwGetMouseButton( buttonNo );
}