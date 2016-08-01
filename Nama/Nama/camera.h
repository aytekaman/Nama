#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "component.h"

enum CameraMode
{
	Orthographic,
	Perspective
};

class Camera : public Component
{
public: //?
	Camera(){};
	~Camera(){};

	void SetToOrthographic();
	void SetToPerspective();

private:

	friend class Renderer;
};

#endif