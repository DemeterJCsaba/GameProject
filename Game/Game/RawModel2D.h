#pragma once

#include<vector>

#include "Maths.h"
#include "RawModel.h"

using namespace std;

class RawModel2D {
protected:
	vector<vec2> m_Vertices;
	vector<vec2> m_Textures;
	vector<unsigned int> m_IndicesVertex;
	vector<unsigned int> m_IndicesTexture;

	vec2 m_Position;
	float m_Rotation;
public:
	RawModel2D(vec2 positon = vec2(), float rotation = 0.0f) : m_Position(positon), m_Rotation(rotation) {}
	
	vector<vec2>& getVertices() { return m_Vertices; }
	vector<vec2>& getTextures() { return m_Textures; }
	vector<unsigned int>& getIndicesVertex() { return m_IndicesVertex; }
	vector<unsigned int>& getIndicesTexture() { return m_IndicesTexture; }

	const vec2& getPosition() const { return m_Position; }
	const float getRotation() const { return m_Rotation; }

	void setPosition(vec2 position) { m_Position = position; }
	void setRotation(float rotation) { m_Rotation += rotation; }
	void addPosition(vec2 position) { m_Position = position; }
	void addRotation(float rotation) { m_Rotation += rotation; }
};