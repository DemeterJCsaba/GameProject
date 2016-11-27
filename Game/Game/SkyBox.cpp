#include "SkyBox.h"


SkyBox::SkyBox(float skySize, float sunSize, float moonSize):
	m_SkySize(skySize),
	m_SunSize(sunSize),
	m_MoonSize(moonSize)
{
	// SkyBox
	m_Vertices.push_back(SkyBoxVertexData(vec3(m_SkySize, m_SkySize, -m_SkySize)));
	m_Vertices.push_back(SkyBoxVertexData(vec3(m_SkySize, m_SkySize, m_SkySize)));
	m_Vertices.push_back(SkyBoxVertexData(vec3(-m_SkySize, m_SkySize, m_SkySize)));
	m_Vertices.push_back(SkyBoxVertexData(vec3(-m_SkySize, m_SkySize, -m_SkySize)));
	m_Vertices.push_back(SkyBoxVertexData(vec3(m_SkySize, -m_SkySize, -m_SkySize)));
	m_Vertices.push_back(SkyBoxVertexData(vec3(m_SkySize, -m_SkySize, m_SkySize)));
	m_Vertices.push_back(SkyBoxVertexData(vec3(-m_SkySize, -m_SkySize, m_SkySize)));
	m_Vertices.push_back(SkyBoxVertexData(vec3(-m_SkySize, -m_SkySize, -m_SkySize)));

	// Sun
	m_Vertices.push_back(SkyBoxVertexData(vec3(m_SunSize, -m_SunSize, m_SkySize), vec2(0, 0), 1.0f));
	m_Vertices.push_back(SkyBoxVertexData(vec3(m_SunSize, m_SunSize, m_SkySize), vec2(0, 1), 1.0f));
	m_Vertices.push_back(SkyBoxVertexData(vec3(-m_SunSize, m_SunSize, m_SkySize), vec2(1, 1), 1.0f));
	m_Vertices.push_back(SkyBoxVertexData(vec3(-m_SunSize, -m_SunSize, m_SkySize), vec2(1, 0),1.0f));
	
	// Moon
	m_Vertices.push_back(SkyBoxVertexData(vec3(-m_MoonSize, -m_MoonSize, -m_SkySize), vec2(0, 0), 2.0f));
	m_Vertices.push_back(SkyBoxVertexData(vec3(-m_MoonSize, m_MoonSize, -m_SkySize), vec2(0, 1), 2.0f));
	m_Vertices.push_back(SkyBoxVertexData(vec3(m_MoonSize, m_MoonSize, -m_SkySize), vec2(1, 1), 2.0f));
	m_Vertices.push_back(SkyBoxVertexData(vec3(m_MoonSize, -m_MoonSize, -m_SkySize), vec2(1, 0), 2.0f));

	unsigned int skyIndices[] = { 
		0, 1, 4, 1, 5, 4,       // Right
		2, 3, 6, 3, 7, 6,       // Left
		2, 1, 3, 1, 0, 3,       // Top
		7, 4, 6, 4, 5, 6,       // Bottom
		1, 2, 5, 2, 6, 5,       // Back
		3, 0, 7, 0, 4, 7,       // Front
		8, 9, 10, 8, 10, 11,    // Sun
		15, 14, 13, 15, 13, 12  // Moon
	};
	for (unsigned int i : skyIndices)
		m_Indices.push_back(i);

	m_TextureNightSky = new CubeTexture("Resources\\Images\\CubeTextures\\galaxy.png");
	m_SkyGradient = new Texture("Resources\\Images\\SkyGradient.png");
	m_TextureSun = new Texture("Resources\\Images\\sun.png");
	m_TextureMoon = new Texture("Resources\\Images\\moon.png");
}

SkyBox::~SkyBox() {
	if(m_SkyGradient!=nullptr) delete m_SkyGradient;
	if(m_TextureNightSky !=nullptr) delete m_TextureNightSky;
	if(m_TextureSun !=nullptr) delete m_TextureSun;
	if(m_TextureMoon !=nullptr) delete m_TextureMoon;
}