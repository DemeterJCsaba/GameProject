#pragma once

#include <cstddef>

#include "RenderEngine.h"
#include "VertexData.h"
#include "SkyBox.h"

#define SKY_BOX_RENDERER_VERTEX_SIZE   sizeof(SkyBoxVertexData)
#define SKY_BOX_RENDERER_VERTEX_COUNT  (8 + 4 + 4)*SKY_BOX_RENDERER_VERTEX_SIZE
#define SKY_BOX_RENDERER_INDICES_COUNT ((8+4+4)*3)*sizeof(unsigned int)

#define SHADER_VERTEX_INDEX    0
#define SHADER_TEXTURE_INDEX   1
#define SHADER_TEXTUREID_INDEX 2

class SkyBoxRenderEngine: private RenderEngine {
private:
	GLuint m_IndexCount;

	GLuint m_TextureSkyGradientID;
	GLuint m_TextureCubeNightSkyID;
	GLuint m_TextureSunID;
	GLuint m_TextureMoonID;

	SkyBoxVertexData* m_Buffer;
	unsigned int* m_IndexBuffer;
public:
	SkyBoxRenderEngine();
	~SkyBoxRenderEngine();

	void submit(SkyBox& skyBox);
	void flush();
private:
	void begin();
	void end();
};