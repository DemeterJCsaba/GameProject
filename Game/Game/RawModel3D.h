#pragma once

#include "RawModel.h"

template <class T>
class RawModel3D : public RawModel<T> {
protected:
	vec3 m_Position;
	vec3 m_Rotation;
public:
	RawModel3D(vec3 postion = vec3(), vec3 rotation = vec3()) :m_Position(postion), m_Rotation(rotation) {}

	const vec3& getPosition() const { return m_Position; }
	const vec3& getRotation() const { return m_Rotation; }

	void setPosition(vec3 position) { m_Position = position; }
	void setRotation(vec3 rotation) { m_Rotation += rotation; }
	void addPosition(vec3 position) { m_Position = position; }
	void addRotation(vec3 rotation) { m_Rotation += rotation; }
};