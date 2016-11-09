#include "SkyBox.h"


SkyBox::SkyBox() {
	init();
}

SkyBox::~SkyBox() {
	delete m_TextureNightSky;
	delete m_TextureSun;
	delete m_TextureMoon;
}

void SkyBox::init() {
	// SkyBox
	SkyBoxVertexData v0;
	v0.vertex = vec3(m_SkySize, m_SkySize, -m_SkySize);
	m_Vertices.push_back(v0);
	SkyBoxVertexData v1;
	v1.vertex = vec3(m_SkySize, m_SkySize, m_SkySize);
	m_Vertices.push_back(v1);
	SkyBoxVertexData v2;
	v2.vertex = vec3(-m_SkySize, m_SkySize, m_SkySize);
	m_Vertices.push_back(v2);
	SkyBoxVertexData v3;
	v3.vertex = vec3(-m_SkySize, m_SkySize, -m_SkySize);
	m_Vertices.push_back(v3);
	SkyBoxVertexData v4;
	v4.vertex = vec3(m_SkySize, -m_SkySize, -m_SkySize);
	m_Vertices.push_back(v4);
	SkyBoxVertexData v5;
	v5.vertex = vec3(m_SkySize, -m_SkySize, m_SkySize);
	m_Vertices.push_back(v5);
	SkyBoxVertexData v6;
	v6.vertex = vec3(-m_SkySize, -m_SkySize, m_SkySize);
	m_Vertices.push_back(v6);
	SkyBoxVertexData v7;
	v7.vertex = vec3(-m_SkySize, -m_SkySize, -m_SkySize);
	m_Vertices.push_back(v7);

	m_Indices.push_back(7);
	m_Indices.push_back(4);
	m_Indices.push_back(0);
	m_Indices.push_back(7);
	m_Indices.push_back(0);
	m_Indices.push_back(3);

	m_Indices.push_back(6);
	m_Indices.push_back(5);
	m_Indices.push_back(4);
	m_Indices.push_back(6);
	m_Indices.push_back(4);
	m_Indices.push_back(7);

	m_Indices.push_back(2);
	m_Indices.push_back(6);
	m_Indices.push_back(7);
	m_Indices.push_back(2);
	m_Indices.push_back(7);
	m_Indices.push_back(3);

	m_Indices.push_back(5);
	m_Indices.push_back(0);
	m_Indices.push_back(4);
	m_Indices.push_back(5);
	m_Indices.push_back(1);
	m_Indices.push_back(0);

	m_Indices.push_back(6);
	m_Indices.push_back(2);
	m_Indices.push_back(1);
	m_Indices.push_back(6);
	m_Indices.push_back(1);
	m_Indices.push_back(5);

	m_Indices.push_back(2);
	m_Indices.push_back(3);
	m_Indices.push_back(0);
	m_Indices.push_back(2);
	m_Indices.push_back(0);
	m_Indices.push_back(1);

	m_TextureNightSky = new CubeTexture("galaxy");
	
	// Sun
	SkyBoxVertexData s0;
	s0.vertex = vec3(m_SunSize, -m_SunSize, m_SkySize);
	s0.teture = vec2(0, 0);
	s0.textureId = 1.0;
	m_Vertices.push_back(s0);
	SkyBoxVertexData s1;
	s1.vertex = vec3(m_SunSize, m_SunSize, m_SkySize);
	s1.teture = vec2(0, 1);
	s1.textureId = 1.0;
	m_Vertices.push_back(s1);
	SkyBoxVertexData s2;
	s2.vertex = vec3(-m_SunSize, m_SunSize, m_SkySize);
	s2.teture = vec2(1, 1);
	s2.textureId = 1.0;
	m_Vertices.push_back(s2);
	SkyBoxVertexData s3;
	s3.vertex = vec3(-m_SunSize, -m_SunSize, m_SkySize);
	s3.teture = vec2(1, 0);
	s3.textureId = 1.0;
	m_Vertices.push_back(s3);

	m_Indices.push_back(8);
	m_Indices.push_back(9);
	m_Indices.push_back(10);
	m_Indices.push_back(8);
	m_Indices.push_back(10);
	m_Indices.push_back(11);

	m_TextureSun = new Texture("Resources\\Images\\sun.png");

	// Moon
	SkyBoxVertexData m0;
	m0.vertex = vec3(-m_MoonSize, -m_MoonSize, -m_SkySize);
	m0.teture = vec2(0, 0);
	m0.textureId = 2.0;
	m_Vertices.push_back(m0);
	SkyBoxVertexData m1;
	m1.vertex = vec3(-m_MoonSize, m_MoonSize, -m_SkySize);
	m1.teture = vec2(0, 1);
	m1.textureId = 2.0;
	m_Vertices.push_back(m1);
	SkyBoxVertexData m2;
	m2.vertex = vec3(m_MoonSize, m_MoonSize, -m_SkySize);
	m2.teture = vec2(1, 1);
	m2.textureId = 2.0;
	m_Vertices.push_back(m2);
	SkyBoxVertexData m3;
	m3.vertex = vec3(m_MoonSize, -m_MoonSize, -m_SkySize);
	m3.teture = vec2(1, 0);
	m3.textureId = 2.0;
	m_Vertices.push_back(m3);

	m_Indices.push_back(12);
	m_Indices.push_back(13);
	m_Indices.push_back(14);
	m_Indices.push_back(12);
	m_Indices.push_back(14);
	m_Indices.push_back(15);

	m_TextureMoon = new Texture("Resources\\Images\\moon.png");
}