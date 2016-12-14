#include "SkyBox.h"


SkyBox::SkyBox(TextureCube* texture,float size) :
	RawModel3DTextured(texture),
	m_Size(size)
{
	m_Vertices.push_back(vec3(m_Size,   m_Size, -m_Size));
	m_Vertices.push_back(vec3(m_Size,   m_Size,  m_Size));
	m_Vertices.push_back(vec3(-m_Size,  m_Size,  m_Size));
	m_Vertices.push_back(vec3(-m_Size,  m_Size, -m_Size));
	m_Vertices.push_back(vec3(m_Size,  -m_Size, -m_Size));
	m_Vertices.push_back(vec3(m_Size,  -m_Size,  m_Size));
	m_Vertices.push_back(vec3(-m_Size, -m_Size,  m_Size));
	m_Vertices.push_back(vec3(-m_Size, -m_Size, -m_Size));
	m_Normals.push_back(vec3());
	m_Textures.push_back(vec2());
	unsigned int skyVertexIndices[] = {
		0, 1, 4, 1, 5, 4,       // Right
		2, 3, 6, 3, 7, 6,       // Left
		2, 1, 3, 1, 0, 3,       // Top
		7, 4, 6, 4, 5, 6,       // Bottom
		1, 2, 5, 2, 6, 5,       // Back
		3, 0, 7, 0, 4, 7        // Front
	};
	for (unsigned int i : skyVertexIndices) {
		m_IndicesVertex.push_back(i);
		m_IndicesNormal.push_back(0);
		m_IndicesTexture.push_back(0);
	}
}

SkyBox::~SkyBox() {
}