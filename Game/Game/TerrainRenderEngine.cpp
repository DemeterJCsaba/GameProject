#include "TerrainRenderEngine.h"

TerrainRenderEngine::TerrainRenderEngine(unsigned int blockSize):
	m_BlockSize((blockSize < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : ((blockSize > MAX_BLOCK_SIZE)? MAX_BLOCK_SIZE : blockSize)),
	VERTEX_SIZE(sizeof(VertexData3D)),
	INDICES_COUNT(6*((blockSize < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : ((blockSize > MAX_BLOCK_SIZE) ? MAX_BLOCK_SIZE : blockSize))*((blockSize < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : ((blockSize > MAX_BLOCK_SIZE) ? MAX_BLOCK_SIZE : blockSize))*BLOCK_COUNT*sizeof(unsigned int)),
	VERTEX_COUNT(INDICES_COUNT*VERTEX_SIZE)
{
	init();
}

void TerrainRenderEngine::init() {
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, VERTEX_COUNT, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(TERRAIN_VERTEX_INDEX);
	glEnableVertexAttribArray(TERRAIN_NORMAL_INDEX);
	glEnableVertexAttribArray(TERRAIN_COLOR_INDEX);

	glVertexAttribPointer(TERRAIN_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData3D, VertexData3D::vertex)));
	glVertexAttribPointer(TERRAIN_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData3D, VertexData3D::normal)));
	glVertexAttribPointer(TERRAIN_COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData3D, VertexData3D::color)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICES_COUNT, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

TerrainRenderEngine::~TerrainRenderEngine() {
	
}

void TerrainRenderEngine::submit(Terrain* terrain, vec2 position) {
	m_Terrain = terrain;
	update(position);
}

void TerrainRenderEngine::flush(vec2 position) {
	if (m_Terrain != nullptr) {
		//update(position);
	}
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glDrawElements(GL_TRIANGLES, INDICES_COUNT, GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TerrainRenderEngine::update(vec2 position) {
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	VertexData3D* m_Buffer = (VertexData3D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	int* m_IndexBuffer = (int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

	int indexCount = 0;
	int n = -(signed int)m_BlockSize;
	int m = 2 * m_BlockSize;
	float s = 5;//m_Terrain->getSize();
	for (int i = n; i < m; ++i) {
		for (int j = n; j < m; ++j) {
			m_Buffer->vertex = vec3(i*s, m_Terrain->getHeight(i,j), j*s);
			++m_Buffer;
			m_Buffer->vertex = vec3(i*s, m_Terrain->getHeight(i, j+1), (j + 1)*s);
			++m_Buffer;
			m_Buffer->vertex = vec3((i + 1)*s, m_Terrain->getHeight(i+1, j+1), (j + 1)*s);
			++m_Buffer;
			m_Buffer->vertex = vec3((i + 1)*s, m_Terrain->getHeight(i+1, j), j*s);
			++m_Buffer;
			(*m_IndexBuffer) = indexCount + 0;
			m_IndexBuffer++;
			(*m_IndexBuffer) = indexCount + 1;
			m_IndexBuffer++;
			(*m_IndexBuffer) = indexCount + 2;
			m_IndexBuffer++;
			(*m_IndexBuffer) = indexCount + 0;
			m_IndexBuffer++;
			(*m_IndexBuffer) = indexCount + 2;
			m_IndexBuffer++;
			(*m_IndexBuffer) = indexCount + 3;
			m_IndexBuffer++;
			indexCount += 4;
		}
	}
	
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
