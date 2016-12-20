#pragma once

#include "Maths.h"
#include "RawModel3D.h"
#include "Window.h"
#include "Terrain.h"

class Camera {
public:
	static Camera* current;

private:
	RawModel3D* m_Entity;
	float m_Distance;

	float m_Speed;

	vec3 m_Position;
	vec3 m_Rotation;
public:
	Camera(float distance = 10.0f);
	void setCurrentCamera(){ current = this; }
	void setEntity(RawModel3D* entity) { m_Entity = entity; }
	void relaseEntity() { m_Entity = nullptr; }
	
	void update();
	mat4 getMatrix();
	mat4 getRotationMatrix();

	vec2 getVerPos() { return vec2(m_Position.x,m_Position.z); }
};