#pragma once

#include <vector>

#include "VertexData.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "RawModel3DTextured.h"

using namespace std;

class SkyBox {
private:
	RawModel3DTextured m_Sky;
	RawModel3DTextured m_Sun;
	RawModel3DTextured m_Moon;

	float m_SkySize;
	float m_SunSize;
	float m_MoonSize;
public:
	SkyBox(float skySize = 100.0f, float sunSize = 5.0f, float moonSize = 4.0f);
	~SkyBox();

	RawModel3DTextured& getSkyModel() { return m_Sky; }
	RawModel3DTextured& getSunModel() { return m_Sun; }
	RawModel3DTextured& getMoonModel() { return m_Moon; }
};