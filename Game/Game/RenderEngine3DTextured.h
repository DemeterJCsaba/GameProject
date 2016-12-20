#pragma once

#include "RenderEngine.h"
#include "RawModel3DTextured.h"

class RenderEngine3DTextured : private RenderEngine {
private:
	struct VertexData3DTextured {
		vec3 vertex;
		vec3 normal;
		vec2 texture;
		float tetureId;
	};
	const int VERTEX_INDEX = 0;
	const int NORMAL_INDEX = 1;
	const int TEXTURE_INDEX = 2;
	const int TEXTUREID_INDEX = 3;
	int m_MaxVertexSize;

	VertexData3DTextured* m_VertexBuffer;
	unsigned int* m_IndexBuffer;
	GLuint m_IndexCount;
	GLuint m_VertexCount;

	bool m_DisableDepth;

	vector<Texture*> m_Textures;
public:
	RenderEngine3DTextured(bool disableDepth = false,int maxVertexSize = 3000);

	void begin();
	void end();
	void submit(RawModel3DTextured& model);

	int addTexture(Texture* texture);

	void flush();
};