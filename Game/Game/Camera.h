#pragma once

#include "Maths.h"
#include "Movable.h"
#include "Window.h"
#include "Terrain.h"

class Camera {
private:
	static const float Default_Speed;
public:
	static Camera* Current;

private:
	Movable* m_Entity;

	vec3 m_Position;
	vec3 m_Rotation;

	float m_Distance;
	float m_Speed;
public:
	Camera(vec3 position = vec3(), vec3 rotation = vec3(),float distance = 10.0f,float speed = Default_Speed);

	void setCurrentCamera(){ Current = this; }

	void setEntity(Movable* entity) { m_Entity = entity; }
	void relaseEntity();
	
	void update();

	mat4 getMatrix();
	mat4 getRotationMatrix();

	vec3 getPosition();
};