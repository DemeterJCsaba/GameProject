#include "SkyBoxRenderEngine.h"

SkyBoxRenderEngine::SkyBoxRenderEngine() {
	init();
}

void SkyBoxRenderEngine::init() {
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, SKY_BOX_RENDERER_VERTEX_COUNT, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
	glEnableVertexAttribArray(SHADER_TEXTUREID_INDEX);

	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, SKY_BOX_RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(SkyBoxVertexData, SkyBoxVertexData::vertex)));
	glVertexAttribPointer(SHADER_TEXTURE_INDEX, 2, GL_FLOAT, GL_FALSE, SKY_BOX_RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(SkyBoxVertexData, SkyBoxVertexData::teture)));
	glVertexAttribPointer(SHADER_TEXTUREID_INDEX, 1, GL_FLOAT, GL_FALSE, SKY_BOX_RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(SkyBoxVertexData, SkyBoxVertexData::textureId)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SKY_BOX_RENDERER_INDICES_COUNT, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

SkyBoxRenderEngine::~SkyBoxRenderEngine() {

}

void SkyBoxRenderEngine::submit(SkyBox& skyBox) {
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	SkyBoxVertexData* m_Buffer = (SkyBoxVertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	unsigned int* m_IndexBuffer = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

	vector<SkyBoxVertexData>& vertices = skyBox.getVertices();
	vector<unsigned int>& indices = skyBox.getIndices();
	Texture* skyGraident = skyBox.getTextureSkyGradient();
	CubeTexture* nightSky = skyBox.getTextureNightSky();
	Texture* sun = skyBox.getTextureSun();
	Texture*moon = skyBox.getTextureMoon();

	for (SkyBoxVertexData& v : vertices) {
		*m_Buffer = v;
		++m_Buffer;
	}

	for (unsigned int i : indices) {
		*m_IndexBuffer = i;
		++m_IndexBuffer;
	}

	m_IndexCount = indices.size();

	m_TextureSkyGradientID = skyGraident->getTextureID();
	m_TextureCubeNightSkyID = nightSky->getTextureID();
	m_TextureSunID = sun->getTextureID();
	m_TextureMoonID = moon->getTextureID();

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SkyBoxRenderEngine::flush() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TextureSkyGradientID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureCubeNightSkyID);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_TextureSunID);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_TextureMoonID);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glDisable(GL_DEPTH_TEST);

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

	glEnable(GL_DEPTH_TEST);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}