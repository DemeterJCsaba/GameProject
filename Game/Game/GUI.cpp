#include "GUI.h"

GUI::GUI(float x, float y) :
	m_Position(vec2(x, y))
{
	tmp();
}

GUI::GUI(float x, float y,Texture* texture):
	m_Position(vec2(x, y)),
	m_Texture(texture)
{
	tmp();
}

void GUI::tmp() {
	// Temporal
	VertexData2D v1;
	v1.vertex = vec2(-1, -1);
	//v1.vertex = vec2(-0.5,-0.5);
	v1.texture = vec2(0, 0);
	v1.color = vec3(1, 0, 0);
	m_Vertices.push_back(v1);

	VertexData2D v2;
	v2.vertex = vec2(-1, 1);
	//v2.vertex = vec2(-0.5, 0.5);
	v2.texture = vec2(0, 1);
	v2.color = vec3(0, 1, 0);
	m_Vertices.push_back(v2);

	VertexData2D v3;
	v3.vertex = vec2(1, 1);
	//v3.vertex = vec2(0.5, 0.5);
	v3.texture = vec2(1,1);
	v3.color = vec3(0, 0, 1);
	m_Vertices.push_back(v3);

	VertexData2D v4;
	//v4.vertex = vec2(0.5, -0.5);
	v4.vertex = vec2(1, -1);
	v4.texture = vec2(1, 0);
	v4.color = vec3(1, 1, 1);
	m_Vertices.push_back(v4);

	m_Indices.push_back(0);
	m_Indices.push_back(1);
	m_Indices.push_back(2);
	m_Indices.push_back(0);
	m_Indices.push_back(2);
	m_Indices.push_back(3);
}