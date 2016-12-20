#pragma once

#include <cstddef>
#include <vector>

#include "RenderEngine.h"
#include "RawModel2D.h"
#include "Texture.h"

class RenderEngine2D: private RenderEngine {
private:
	struct VertexData2D {
		vec2 vertex;
		vec2 texture;
		float textureId;
	};
	const int VERTEX_INDEX = 0;
	const int TEXTURE_INDEX = 1;
	const int TEXTUREID_INDEX = 2;
	int m_MaxVertexSize;

	VertexData2D* m_VertexBuffer;
	unsigned int* m_IndexBuffer;
	GLuint m_IndexCount;
	GLuint m_VertexCount;

	bool m_DisableDepth;

	vector<Texture*> m_Textures;

	vector<vec2> m_TransformationStack;
public:
	RenderEngine2D(bool disableDepth = false, int maxVertexSize = 1000);

	void begin();
	void end();
	void submit(RawModel2D* model);

	void flush();
private:
	void submitModel(RawModel2D* model);
};