#pragma once

#include <vector>
#include <string>

#include "Maths.h"

using namespace std;

class RawModel3D {
protected:
	vector<vec3> m_Vertices;
	vector<vec3> m_Normals;
	vector<vec3> m_Colors;
	vector<unsigned int> m_IndicesVertex;
	vector<unsigned int> m_IndicesNormal;
	vector<unsigned int> m_IndicesColor;

	vec3 m_Position;
	vec3 m_Rotation;
public:
	RawModel3D(vec3 postion = vec3(), vec3 rotation = vec3()) :m_Position(postion), m_Rotation(rotation) {}
	
	vector<vec3>& getVertices() { return m_Vertices; }
	vector<vec3>& getNormals() { return m_Normals; }
	vector<vec3>& getColors() { return m_Colors; }
	vector<unsigned int>& getIndicesVertex() { return m_IndicesVertex; }
	vector<unsigned int>& getIndicesNormal() { return m_IndicesNormal; }
	vector<unsigned int>& getIndicesColor() { return m_IndicesColor; }

	const vec3& getPosition() const { return m_Position; }
	const vec3& getRotation() const { return m_Rotation; }

	void setPosition(vec3 position) { m_Position = position; }
	void setRotation(vec3 rotation) { m_Rotation = rotation; }
	void addPosition(vec3 position) { m_Position += position; }
	void addRotation(vec3 rotation) { m_Rotation += rotation; }

	void loadFromOBJ(string fileName); // friend 
};