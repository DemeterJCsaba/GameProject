#pragma once

#include<vector>

#include "Maths.h"
#include "Texture.h"

using namespace std;

class RawModel3DTextured {
protected:
	vector<vec3> m_Vertices;
	vector<vec3> m_Normals;
	vector<vec2> m_Textures;
	vector<unsigned int> m_IndicesVertex;
	vector<unsigned int> m_IndicesNormal;
	vector<unsigned int> m_IndicesTexture;

	Texture* m_Texture;

	vec3 m_Position;
	vec3 m_Rotation;
public:
	RawModel3DTextured(Texture* texture,vec3 postion = vec3(), vec3 rotation = vec3()) :m_Texture(texture),m_Position(postion), m_Rotation(rotation) {}
	
	vector<vec3>& getVertices() { return m_Vertices; }
	vector<vec3>& getNormals() { return m_Normals; }
	vector<vec2>& getTextures() { return m_Textures; }
	vector<unsigned int>& getIndicesVertex() { return m_IndicesVertex; }
	vector<unsigned int>& getIndicesNormal() { return m_IndicesNormal; }
	vector<unsigned int>& getIndicesTexture() { return m_IndicesTexture; }

	Texture* getTexture() const { return m_Texture; }

	const vec3& getPosition() const { return m_Position; }
	const vec3& getRotation() const { return m_Rotation; }

	void setPosition(vec3 position) { m_Position = position; }
	void setRotation(vec3 rotation) { m_Rotation = rotation; }
	void addPosition(vec3 position) { m_Position += position; }
	void addRotation(vec3 rotation) { m_Rotation += rotation; }
};