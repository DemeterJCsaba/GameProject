#pragma once

#include "Maths.h"

class Camera {
public:
	static Camera* current;

private:
	vec3 m_Position;
	vec3 m_Rotation;
public:
	Camera();
	mat4 getMatrix();
	void setCurrentCamera();

	void tmp(vec3 moove,vec3 rotate);
};