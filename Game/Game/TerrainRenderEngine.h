#pragma once

#include <stdio.h>
#include <cstddef>
#include <GLEW\glew.h>

#include "VertexData.h"
#include "Terrain.h"
#include "Texture.h"

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

	const int BLOCK_COUNT = 9;
	const int VERTEX_SIZE;
	const int INDICES_COUNT;
	const int VERTEX_COUNT;

	unsigned int m_BlockSize;
	Terrain* m_Terrain;

	int m_IndexLeftFront;
	int m_IndexMidleFront;
	int m_IndexRightFront;
	int m_IndexLeftMidle;
	int m_IndexMidleMidle;
	int m_IndexRightMidle;
	int m_IndexLeftBottom;
	int m_IndexMidleBottom;
	int m_IndexRightBottom;

	int m_CurrentXInd;
	int m_CurrentYInd;

	float m_HeightBuffer[MAX_BLOCK_SIZE][MAX_BLOCK_SIZE];
	bool m_HeightIsLoadedBuffer[MAX_BLOCK_SIZE][MAX_BLOCK_SIZE];

	VertexData3D* m_Buffer;
	int* m_IndexBuffer;

	Texture* m_SkyGradient;
public:
	TerrainRenderEngine(unsigned int blockSize);
	~TerrainRenderEngine();

	void submit(Terrain* terrain,vec2 position);
	void flush(vec2 position);
private:
	void init();
	void begin();
	void updateBlock(int x, int y, const int ind);
	void end();

	int posToIndex(float value);
};