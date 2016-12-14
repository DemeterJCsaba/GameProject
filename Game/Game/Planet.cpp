#include "Planet.h"

Planet::Planet(Texture2D* texture, float distance, vec3 orbit,float size):
	RawModel3DTextured(texture,vec3(),orbit),
	m_Size(size)
{
	m_Vertices.push_back(vec3(m_Size,  -m_Size, distance));
	m_Vertices.push_back(vec3(m_Size,  m_Size,  distance));
	m_Vertices.push_back(vec3(-m_Size, m_Size,  distance));
	m_Vertices.push_back(vec3(-m_Size, -m_Size, distance));
	m_Textures.push_back(vec2(0.0f, 0.0f));
	m_Textures.push_back(vec2(0.0f, 1.0f));
	m_Textures.push_back(vec2(1.0f, 1.0f));
	m_Textures.push_back(vec2(1.0f, 0.0f));
	m_Normals.push_back(vec3());
	unsigned int sunVertexIndices[] = { 0, 1, 2, 0, 2, 3 };
	unsigned int sunTextureIndices[] = { 0, 1, 2, 0, 2, 3 };
	for (int i = 0; i<6; ++i) {
		m_IndicesVertex.push_back(sunVertexIndices[i]);
		m_IndicesTexture.push_back(sunTextureIndices[i]);
		m_IndicesNormal.push_back(0);
	}
}