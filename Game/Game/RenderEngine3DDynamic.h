#pragma once

#include <vector>
#include <cstddef>

#include "RenderEngine.h"
#include "VertexData.h"
#include "Entity.h"

#define MAX_SIZE      10000
#define VERTEX_SIZE   sizeof(VertexData3D)
#define VERTEX_COUNT  MAX_SIZE*VERTEX_SIZE*3
#define INDICES_COUNT MAX_SIZE*sizeof(unsigned int)*3

#define VERTEX_INDEX  0
#define NORMAL_INDEX  1
#define COLOR_INDEX   2

using namespace std;

class RenderEngine3DDynamic : private RenderEngine {
private:
	GLuint m_IndexCount;
	GLuint m_VertexCount;

	VertexData3D* m_Buffer;
	unsigned int* m_IndexBuffer;

	vector<RawModel3D*> m_Entities;
public:
	RenderEngine3DDynamic();
	~RenderEngine3DDynamic();

	void submit(RawModel3D* entity);
	void flush(vec2 pos = vec2(0.0f,0.0f));
private:
	void begin();
	void end();
};