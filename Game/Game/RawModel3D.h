#pragma once

#include <vector>
#include <string>

#include "Maths.h"

using namespace std;

class RawModel3D {
private:
	static string m_Dir;

protected:
	vector<vec3> m_Vertices;
	vector<vec3> m_Normals;
	vector<vec3> m_Colors;
	vector<unsigned int> m_IndicesVertex;
	vector<unsigned int> m_IndicesNormal;
	vector<unsigned int> m_IndicesColor;

	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;
public:
	RawModel3D(vec3 postion = vec3(), vec3 rotation = vec3(), vec3 scale = vec3(1.0f)) :m_Position(postion), m_Rotation(rotation),m_Scale(scale) {}
	
	vector<vec3>& getVertices() { return m_Vertices; }
	vector<vec3>& getNormals() { return m_Normals; }
	vector<vec3>& getColors() { return m_Colors; }
	vector<unsigned int>& getIndicesVertex() { return m_IndicesVertex; }
	vector<unsigned int>& getIndicesNormal() { return m_IndicesNormal; }
	vector<unsigned int>& getIndicesColor() { return m_IndicesColor; }

	const vec3& getPosition() const { return m_Position; }
	const vec3& getRotation() const { return m_Rotation; }
	const vec3& getScale() const { return m_Scale; }

	void setPosition(vec3 position) { m_Position = position; }
	void setRotation(vec3 rotation) { m_Rotation = rotation; }
	void setScale(vec3 scale) { m_Scale = scale; }
	void addPosition(vec3 position) { m_Position += position; }
	void addRotation(vec3 rotation) { m_Rotation += rotation; }
	void addScale(vec3 scale) { m_Scale += scale; }

	void loadFromOBJ(string fileName); // friend 
};