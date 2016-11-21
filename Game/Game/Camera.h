#pragma once

#include "Maths.h"
#include "Entity.h"
#include "Window.h"

class Camera {
public:
	static Camera* current;

private:
	Entity* m_Entity;

	float m_Speed;

	vec3 m_Position;
	vec3 m_Rotation;
public:
	Camera();
	void setCurrentCamera(){ current = this; }
	void setEntity(Entity* entity) { m_Entity = entity; }
	void relaseEntity() { m_Entity = nullptr; }
	
	void update();
	mat4 getMatrix();
	mat4 getRotationMatrix();

	vec2 getVerPos() { return vec2(m_Position.x,m_Position.z); }
};