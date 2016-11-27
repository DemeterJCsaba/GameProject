#pragma once

#include <vector>

#include "VertexData.h"
#include "Texture.h"
#include "CubeTexture.h"
#include "RawModel.h"

using namespace std;

class SkyBox : public RawModel<SkyBoxVertexData>{
private:
	float m_SkySize;
	float m_SunSize;
	float m_MoonSize;

	Texture* m_SkyGradient = nullptr;
	CubeTexture* m_TextureNightSky = nullptr;
	Texture* m_TextureSun = nullptr;
	Texture* m_TextureMoon = nullptr;
public:
	SkyBox(float skySize = 100.0f, float sunSize = 5.0f, float moonSize = 4.0f);
	~SkyBox();

	Texture* getTextureSkyGradient() { return m_SkyGradient; }
	CubeTexture* getTextureNightSky() { return m_TextureNightSky; }
	Texture* getTextureSun() { return m_TextureSun; }
	Texture* getTextureMoon() { return m_TextureMoon; }
};