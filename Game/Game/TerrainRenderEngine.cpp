#include "TerrainRenderEngine.h"

TerrainRenderEngine::TerrainRenderEngine(unsigned int blockSize):
	m_BlockSize((blockSize < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : ((blockSize > MAX_BLOCK_SIZE)? MAX_BLOCK_SIZE : blockSize)),
	VERTEX_SIZE(sizeof(VertexData3D)),
	INDICES_COUNT(6 * ((blockSize < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : ((blockSize > MAX_BLOCK_SIZE) ? MAX_BLOCK_SIZE : blockSize))*((blockSize < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : ((blockSize > MAX_BLOCK_SIZE) ? MAX_BLOCK_SIZE : blockSize))*BLOCK_COUNT*sizeof(unsigned int)),
	VERTEX_COUNT(6 * ((blockSize < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : ((blockSize > MAX_BLOCK_SIZE) ? MAX_BLOCK_SIZE : blockSize))*((blockSize < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : ((blockSize > MAX_BLOCK_SIZE) ? MAX_BLOCK_SIZE : blockSize))*BLOCK_COUNT*VERTEX_SIZE)
{
	init();

	int block = 6 * blockSize*blockSize;//*VERTEX_SIZE;
	m_IndexLeftFront   = 0 * block;
	m_IndexMidleFront  = 1 * block;
	m_IndexRightFront  = 2 * block;
	m_IndexLeftMidle   = 3 * block;
	m_IndexMidleMidle  = 4 * block;
	m_IndexRightMidle  = 5 * block;
	m_IndexLeftBottom  = 6 * block;
	m_IndexMidleBottom = 7 * block;
	m_IndexRightBottom = 8 * block;

	m_SkyGradient = new Texture("Resources\\Images\\SkyGradient.png");
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
	m_CurrentXInd = posToIndex(position.x);
	m_CurrentYInd = posToIndex(position.y);
	begin();
	updateBlock(m_CurrentXInd - 1, m_CurrentYInd - 1, m_IndexLeftFront);
	updateBlock(m_CurrentXInd + 0, m_CurrentYInd - 1, m_IndexMidleFront);
	updateBlock(m_CurrentXInd + 1, m_CurrentYInd - 1, m_IndexRightFront);
	updateBlock(m_CurrentXInd - 1, m_CurrentYInd + 0, m_IndexLeftMidle);
	updateBlock(m_CurrentXInd + 0, m_CurrentYInd + 0, m_IndexMidleMidle);
	updateBlock(m_CurrentXInd + 1, m_CurrentYInd + 0, m_IndexRightMidle);
	updateBlock(m_CurrentXInd - 1, m_CurrentYInd + 1, m_IndexLeftBottom);
	updateBlock(m_CurrentXInd + 0, m_CurrentYInd + 1, m_IndexMidleBottom);
	updateBlock(m_CurrentXInd + 1, m_CurrentYInd + 1, m_IndexRightBottom);
	end();
}

void TerrainRenderEngine::flush(vec2 position) {
	if (m_Terrain != nullptr) {
		int newXind = posToIndex(position.x);
		int newYind = posToIndex(position.y);
		if (newXind != m_CurrentXInd || newYind != m_CurrentYInd) {
			begin();
			if (newXind != m_CurrentXInd) {
				if (newXind > m_CurrentXInd) { // +x
					int tmp1 = m_IndexLeftFront;
					int tmp2 = m_IndexLeftMidle;
					int tmp3 = m_IndexLeftBottom;

					m_IndexLeftFront  = m_IndexMidleFront;
					m_IndexLeftMidle  = m_IndexMidleMidle;
					m_IndexLeftBottom = m_IndexMidleBottom;
					m_IndexMidleFront  = m_IndexRightFront;
					m_IndexMidleMidle  = m_IndexRightMidle;
					m_IndexMidleBottom = m_IndexRightBottom;
					m_IndexRightFront  = tmp1;
					m_IndexRightMidle  = tmp2;
					m_IndexRightBottom = tmp3;

					updateBlock(newXind + 1, m_CurrentYInd - 1, tmp1);
					updateBlock(newXind + 1, m_CurrentYInd + 0, tmp2);
					updateBlock(newXind + 1, m_CurrentYInd + 1, tmp3);
				}
				else { // -x
					int tmp1 = m_IndexRightFront;
					int tmp2 = m_IndexRightMidle;
					int tmp3 = m_IndexRightBottom;

					m_IndexRightFront = m_IndexMidleFront;
					m_IndexRightMidle = m_IndexMidleMidle;
					m_IndexRightBottom = m_IndexMidleBottom;
					m_IndexMidleFront = m_IndexLeftFront;
					m_IndexMidleMidle = m_IndexLeftMidle;
					m_IndexMidleBottom = m_IndexLeftBottom;
					m_IndexLeftFront = tmp1;
					m_IndexLeftMidle = tmp2;
					m_IndexLeftBottom = tmp3;

					updateBlock(newXind - 1, m_CurrentYInd - 1, tmp1);
					updateBlock(newXind - 1, m_CurrentYInd + 0, tmp2);
					updateBlock(newXind - 1, m_CurrentYInd + 1, tmp3);
				}
				m_CurrentXInd = newXind;
			}else{
				if (newYind > m_CurrentYInd) { // +z
					int tmp1 = m_IndexLeftFront;
					int tmp2 = m_IndexMidleFront;
					int tmp3 = m_IndexRightFront;

					m_IndexLeftFront = m_IndexLeftMidle;
					m_IndexMidleFront = m_IndexMidleMidle;
					m_IndexRightFront = m_IndexRightMidle;
					m_IndexLeftMidle = m_IndexLeftBottom;
					m_IndexMidleMidle = m_IndexMidleBottom;
					m_IndexRightMidle = m_IndexRightBottom;
					m_IndexLeftBottom = tmp1;
					m_IndexMidleBottom = tmp2;
					m_IndexRightBottom = tmp3;

					updateBlock(m_CurrentXInd - 1, newYind + 1, tmp1);
					updateBlock(m_CurrentXInd + 0, newYind + 1, tmp2);
					updateBlock(m_CurrentXInd + 1, newYind + 1, tmp3);
				} else { // -z
					int tmp1 = m_IndexLeftBottom;
					int tmp2 = m_IndexMidleBottom;
					int tmp3 = m_IndexRightBottom;

					m_IndexLeftBottom = m_IndexLeftMidle;
					m_IndexMidleBottom = m_IndexMidleMidle;
					m_IndexRightBottom = m_IndexRightMidle;
					m_IndexLeftMidle = m_IndexLeftFront;
					m_IndexMidleMidle = m_IndexMidleFront;
					m_IndexRightMidle = m_IndexRightFront;
					m_IndexLeftFront = tmp1;
					m_IndexMidleFront = tmp2;
					m_IndexRightFront = tmp3;

					updateBlock(m_CurrentXInd - 1, newYind - 1, tmp1);
					updateBlock(m_CurrentXInd + 0, newYind - 1, tmp2);
					updateBlock(m_CurrentXInd + 1, newYind - 1, tmp3);
				}
				m_CurrentYInd = newYind;
			}
			end();
		}
	}

	glActiveTexture(GL_TEXTURE0);
	m_SkyGradient->bind();

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glDrawElements(GL_TRIANGLES, INDICES_COUNT, GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TerrainRenderEngine::begin() {
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	m_Buffer = (VertexData3D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	m_IndexBuffer = (int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void TerrainRenderEngine::end() {
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TerrainRenderEngine::updateBlock(int x, int y,const int ind) {
	for (int i = 0; i <= m_BlockSize; ++i) {
		for (int j = 0; j <= m_BlockSize; ++j) {
			m_HeightIsLoadedBuffer[i][j] = false;
		}
	}

	int indexCount = 0;

	int n1 = x*((signed int)m_BlockSize);
	int m1 = (x+1)*((signed int)m_BlockSize);
	int n2 = y*((signed int)m_BlockSize);
	int m2 = (y + 1)*((signed int)m_BlockSize);

	float s = m_Terrain->getSize();

	for (int i = n1; i < m1; ++i) {
		for (int j = n2; j < m2; ++j) {
			int index = ind + indexCount;
			int ii = i - n1;
			int jj = j - n2;
			if (!m_HeightIsLoadedBuffer[ii][jj]) { 
				m_HeightBuffer[ii][jj] = m_Terrain->getHeight(i, j); 
				m_HeightIsLoadedBuffer[ii][jj] = true;
			}
			if (!m_HeightIsLoadedBuffer[ii][jj + 1]) { 
				m_HeightBuffer[ii][jj + 1] = m_Terrain->getHeight(i, j + 1); 
				m_HeightIsLoadedBuffer[ii][jj+1] = true;
			}
			if (!m_HeightIsLoadedBuffer[ii + 1][jj + 1]) {
				m_HeightBuffer[ii + 1][jj + 1] = m_Terrain->getHeight(i + 1, j + 1);
				m_HeightIsLoadedBuffer[ii+1][jj+1] = true;
			}
			if (!m_HeightIsLoadedBuffer[ii + 1][jj]) {
				m_HeightBuffer[ii + 1][jj] = m_Terrain->getHeight(i + 1, j);
				m_HeightIsLoadedBuffer[ii+1][jj] = true;
			}
			vec3 a = vec3(i*s, m_HeightBuffer[ii][jj], j*s);
			vec3 b = vec3(i*s, m_HeightBuffer[ii][jj + 1], (j + 1)*s);
			vec3 c = vec3((i + 1)*s, m_HeightBuffer[ii + 1][jj + 1], (j + 1)*s);
			vec3 d = vec3((i + 1)*s, m_HeightBuffer[ii + 1][jj], j*s);
			vec3 norm1 = norm(a, b, c);
			vec3 norm2 = norm(a, c, d);
			vec3 color = vec3(0.2705, 0.545, 0.0);

			if (((i < 0 ? -i : i) + (j < 0 ? -j : j)) % 2 == 0) {
				m_Buffer[index + 0].vertex = a;
				m_Buffer[index + 1].vertex = b;
				m_Buffer[index + 2].vertex = c;

				m_Buffer[index + 3].vertex = a;
				m_Buffer[index + 4].vertex = c;
				m_Buffer[index + 5].vertex = d;
			} else {
				m_Buffer[index + 0].vertex = b;
				m_Buffer[index + 1].vertex = c;
				m_Buffer[index + 2].vertex = d;

				m_Buffer[index + 3].vertex = b;
				m_Buffer[index + 4].vertex = d;
				m_Buffer[index + 5].vertex = a;
			}

			m_Buffer[index + 0].color = color;
			m_Buffer[index + 1].color = color;
			m_Buffer[index + 2].color = color;
			m_Buffer[index + 3].color = color;
			m_Buffer[index + 4].color = color;
			m_Buffer[index + 5].color = color;

			m_Buffer[index + 0].normal = norm1;
			m_Buffer[index + 1].normal = norm1;
			m_Buffer[index + 2].normal = norm1;
			m_Buffer[index + 3].normal = norm2;
			m_Buffer[index + 4].normal = norm2;
			m_Buffer[index + 5].normal = norm2;

			m_IndexBuffer[index + 0] = index + 0;
			m_IndexBuffer[index + 1] = index + 1;
			m_IndexBuffer[index + 2] = index + 2;
			m_IndexBuffer[index + 3] = index + 3;
			m_IndexBuffer[index + 4] = index + 4;
			m_IndexBuffer[index + 5] = index + 5;

			indexCount += 6;
		}
	}
}

int TerrainRenderEngine::posToIndex(float value) {
	return (int)(value / (m_BlockSize*m_Terrain->getSize())) - (value<0?1:0);
}
