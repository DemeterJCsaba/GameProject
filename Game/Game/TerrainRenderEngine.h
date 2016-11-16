#pragma once

#include <stdio.h>
#include <cstddef>
#include <GLEW\glew.h>

#include "VertexData.h"
#include "Terrain.h"

#define MIN_BLOCK_SIZE 8
#define MAX_BLOCK_SIZE 256

#define TERRAIN_DISTANCE 3

#define TERRAIN_VERTEX_INDEX  0
#define TERRAIN_NORMAL_INDEX  1
#define TERRAIN_COLOR_INDEX   2

class TerrainRenderEngine {
private:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;

	unsigned int BLOCK_COUNT = 9;
	unsigned int VERTEX_SIZE;
	unsigned int INDICES_COUNT;
	unsigned int VERTEX_COUNT;

	unsigned int m_BlockSize;
	Terrain* m_Terrain;
public:
	TerrainRenderEngine(unsigned int blockSize);
	~TerrainRenderEngine();

	void submit(Terrain* terrain,vec2 position);
	void flush(vec2 position);
private:
	void init();
	void update(vec2 position);
};