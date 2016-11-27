#pragma once

#include<vector>

#include "VertexData.h"
#include "Maths.h"

using namespace std;

template <class T>
class RawModel{
protected:
	vector<T> m_Vertices;
	vector<unsigned int> m_Indices;

	vec3 m_Position;
	vec3 m_Rotation;
public:
	vector<T>& getVertices() { return m_Vertices; }
	vector<unsigned int>& getIndices() { return m_Indices; }

	const vec3& getPosition() const { return m_Position; }
	const vec3& getRotation() const { return m_Rotation; }

	void setPosition(vec3 position) { m_Position = position; }
	void setRotation(vec3 rotation) { m_Rotation += rotation; }
	void addPosition(vec3 position) { m_Position = position; }
	void addRotation(vec3 rotation) { m_Rotation += rotation; }
};

