#include "SkyBox.h"


SkyBox::SkyBox(float skySize, float sunSize, float moonSize) :
	m_SkySize(skySize),
	m_SunSize(sunSize),
	m_MoonSize(moonSize),
	m_Sky(RawModel3DTextured(new TextureCube("Resources\\Images\\CubeTextures\\galaxy.png"))),
	m_Sun(RawModel3DTextured(new Texture2D("Resources\\Images\\sun.png"))),
	m_Moon(RawModel3DTextured(new Texture2D("Resources\\Images\\moon.png")))
{
	// SkyBox
	m_Sky.getVertices().push_back(vec3(m_SkySize, m_SkySize, -m_SkySize));
	m_Sky.getVertices().push_back(vec3(m_SkySize, m_SkySize, m_SkySize));
	m_Sky.getVertices().push_back(vec3(-m_SkySize, m_SkySize, m_SkySize));
	m_Sky.getVertices().push_back(vec3(-m_SkySize, m_SkySize, -m_SkySize));
	m_Sky.getVertices().push_back(vec3(m_SkySize, -m_SkySize, -m_SkySize));
	m_Sky.getVertices().push_back(vec3(m_SkySize, -m_SkySize, m_SkySize));
	m_Sky.getVertices().push_back(vec3(-m_SkySize, -m_SkySize, m_SkySize));
	m_Sky.getVertices().push_back(vec3(-m_SkySize, -m_SkySize, -m_SkySize));
	m_Sky.getNormals().push_back(vec3());
	m_Sky.getTextures().push_back(vec2());
	unsigned int skyVertexIndices[] = {
		0, 1, 4, 1, 5, 4,       // Right
		2, 3, 6, 3, 7, 6,       // Left
		2, 1, 3, 1, 0, 3,       // Top
		7, 4, 6, 4, 5, 6,       // Bottom
		1, 2, 5, 2, 6, 5,       // Back
		3, 0, 7, 0, 4, 7        // Front
	};
	for (unsigned int i : skyVertexIndices) {
		m_Sky.getIndicesVertex().push_back(i);
		m_Sky.getIndicesNormal().push_back(0);
		m_Sky.getIndicesTexture().push_back(0);
	}

	// Sun
	m_Sun.getVertices().push_back(vec3(m_SunSize, -m_SunSize, m_SkySize));
	m_Sun.getVertices().push_back(vec3(m_SunSize, m_SunSize, m_SkySize));
	m_Sun.getVertices().push_back(vec3(-m_SunSize, m_SunSize, m_SkySize));
	m_Sun.getVertices().push_back(vec3(-m_SunSize, -m_SunSize, m_SkySize));
	m_Sun.getTextures().push_back(vec2(0.0f, 0.0f));
	m_Sun.getTextures().push_back(vec2(0.0f, 1.0f));
	m_Sun.getTextures().push_back(vec2(1.0f, 1.0f));
	m_Sun.getTextures().push_back(vec2(1.0f, 0.0f));
	m_Sun.getNormals().push_back(vec3());
	unsigned int sunVertexIndices[] = { 0, 1, 2, 0, 2, 3 };
	unsigned int sunTextureIndices[] = { 0, 1, 2, 0, 2, 3 };
	for (int i = 0;i<6;++i){
		m_Sun.getIndicesVertex().push_back(sunVertexIndices[i]);
		m_Sun.getIndicesTexture().push_back(sunTextureIndices[i]);
		m_Sun.getIndicesNormal().push_back(0);
	}
	
	// Moon
	m_Moon.getVertices().push_back(vec3(-m_MoonSize, -m_MoonSize, -m_SkySize));
	m_Moon.getVertices().push_back(vec3(-m_MoonSize, m_MoonSize, -m_SkySize));
	m_Moon.getVertices().push_back(vec3(m_MoonSize, m_MoonSize, -m_SkySize));
	m_Moon.getVertices().push_back(vec3(m_MoonSize, -m_MoonSize, -m_SkySize));
	m_Moon.getTextures().push_back(vec2(0.0f, 0.0f));
	m_Moon.getTextures().push_back(vec2(0.0f, 1.0f));
	m_Moon.getTextures().push_back(vec2(1.0f, 1.0f));
	m_Moon.getTextures().push_back(vec2(1.0f, 0.0f));
	m_Moon.getNormals().push_back(vec3());
	unsigned int moonVertexIndices[] = { 0, 2, 1, 0, 2, 3 };// { 3, 1, 2, 3, 0, 1 };
	unsigned int moonTextureIndices[] = { 2, 0, 1, 0, 3, 2 };
	for (int i = 0; i<6; ++i) {
		m_Moon.getIndicesVertex().push_back(sunVertexIndices[i]);
		m_Moon.getIndicesTexture().push_back(sunTextureIndices[i]);
		m_Moon.getIndicesNormal().push_back(0);
	}
}

SkyBox::~SkyBox() {
}