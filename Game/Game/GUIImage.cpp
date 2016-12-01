#include "GUIImage.h"

GUIImage::GUIImage(vec2 position, vec2 size,Texture* texture):
	RawModel2D(texture,position),
	m_Size(size)
{
	m_Vertices.push_back(vec2(0.0f, 0.0f));
	m_Vertices.push_back(vec2(0.0f, 0.0f + m_Size.y));
	m_Vertices.push_back(vec2(0.0f + m_Size.x, 0.0f + m_Size.y));
	m_Vertices.push_back(vec2(0.0f + m_Size.x, 0.0f));

	m_Textures.push_back(vec2(0, 0));
	m_Textures.push_back(vec2(0, 1));
	m_Textures.push_back(vec2(1, 1));
	m_Textures.push_back(vec2(1, 0));

	unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };
	for (unsigned int i : indices) {
		m_IndicesVertex.push_back(i);
		m_IndicesTexture.push_back(i);
	}
}