#pragma once

#include <vector>

#include "VertexData.h"
#include "Texture.h"
#include "CubeTexture.h"

using namespace std;

class SkyBox {
private:
	vector<SkyBoxVertexData> m_Vertices;
	vector<unsigned int> m_Indices;

	Texture* m_SkyGradient = nullptr;
	CubeTexture* m_TextureNightSky = nullptr;
	Texture* m_TextureSun = nullptr;
	Texture* m_TextureMoon = nullptr;

	float m_SkySize = 100;
	float m_SunSize = 5;
	float m_MoonSize = 4;
public:
	SkyBox();
	~SkyBox();

	vector<SkyBoxVertexData>& getVertices() { return m_Vertices; }
	vector<unsigned int>& getIndices() { return m_Indices; }

	Texture* getTextureSkyGradient() { return m_SkyGradient; }
	CubeTexture* getTextureNightSky() { return m_TextureNightSky; }
	Texture* getTextureSun() { return m_TextureSun; }
	Texture* getTextureMoon() { return m_TextureMoon; }
private:
	void init();
};