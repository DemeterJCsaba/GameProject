#pragma once

#include "RawModel.h"

template <class T>
class RawModel2D : public RawModel<T> {
protected:
	vec2 m_Position;
	float m_Rotation;
public:
	RawModel2D(vec2 positon = vec2(),float rotation = 0.0f): m_Position(positon),m_Rotation(rotation){}

	const vec2& getPosition() const { return m_Position; }
	const float getRotation() const { return m_Rotation; }

	void setPosition(vec2 position) { m_Position = position; }
	void setRotation(float rotation) { m_Rotation += rotation; }
	void addPosition(vec2 position) { m_Position = position; }
	void addRotation(float rotation) { m_Rotation += rotation; }
};