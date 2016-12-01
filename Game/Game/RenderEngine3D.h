#pragma once

#include "RenderEngine.h"
#include "RawModel3D.h"

class RenderEngine3D : private RenderEngine {
private:
	struct VertexData3D {
		vec3 vertex;
		vec3 normal;
		vec3 color;
	};
	const int VERTEX_INDEX = 0;
	const int NORMAL_INDEX = 1;
	const int COLOR_INDEX = 2;
	int m_MaxVertexSize;

	VertexData3D* m_VertexBuffer;
	unsigned int* m_IndexBuffer;
	GLuint m_IndexCount;
	GLuint m_VertexCount;

	bool m_DisableDepth;
public:
	RenderEngine3D(bool disableDepth = false, int maxVertexSize = 3000);

	void begin();
	void end();
	void submit(RawModel3D& model);

	void flush();
};