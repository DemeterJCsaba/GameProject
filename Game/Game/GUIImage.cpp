#include "GUIImage.h"

GUIImage::GUIImage(vec2 position, vec2 size,Texture* texture):
	RawModel2D(position),
	m_Size(size),
	m_Texture(texture)
{
	m_Vertices.push_back(VertexData2D(vec2(0.0f, 0.0f), vec2(0, 0)));
	m_Vertices.push_back(VertexData2D(vec2(0.0f, 0.0f + m_Size.y), vec2(0, 1)));
	m_Vertices.push_back(VertexData2D(vec2(0.0f + m_Size.x, 0.0f + m_Size.y), vec2(1, 1)));
	m_Vertices.push_back(VertexData2D(vec2(0.0f + m_Size.x, 0.0f), vec2(1, 0)));
	unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };
	for (unsigned int i : indices) m_Indices.push_back(i);
}