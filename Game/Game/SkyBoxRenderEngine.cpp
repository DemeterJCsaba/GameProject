#include "SkyBoxRenderEngine.h"

SkyBoxRenderEngine::SkyBoxRenderEngine() {
	bindVAO();
		bindVBO();
		glBufferData(GL_ARRAY_BUFFER, SKY_BOX_RENDERER_VERTEX_COUNT, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
		glEnableVertexAttribArray(SHADER_TEXTUREID_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, SKY_BOX_RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(SkyBoxVertexData, SkyBoxVertexData::vertex)));
		glVertexAttribPointer(SHADER_TEXTURE_INDEX, 2, GL_FLOAT, GL_FALSE, SKY_BOX_RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(SkyBoxVertexData, SkyBoxVertexData::texture)));
		glVertexAttribPointer(SHADER_TEXTUREID_INDEX, 1, GL_FLOAT, GL_FALSE, SKY_BOX_RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(SkyBoxVertexData, SkyBoxVertexData::textureId)));
		unbindVBO();

		bindIBO();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, SKY_BOX_RENDERER_INDICES_COUNT, NULL, GL_DYNAMIC_DRAW);
		unbindIBO();
	unbindVAO();
}

SkyBoxRenderEngine::~SkyBoxRenderEngine() {

}

void SkyBoxRenderEngine::begin() {
	bindVBO();
	m_Buffer = (SkyBoxVertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	bindIBO();
	m_IndexBuffer = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void SkyBoxRenderEngine::end() {
	glUnmapBuffer(GL_ARRAY_BUFFER);
	unbindVBO();
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	unbindIBO();
}

void SkyBoxRenderEngine::submit(SkyBox& skyBox) {
	begin();

	vector<vec3>& vertecies = skyBox.getVertices();
	vector<vec2>& textures = skyBox.getTextures();
	vector<unsigned int>& indicesVertex = skyBox.getIndicesVertex();
	vector<unsigned int>& indicesTexture = skyBox.getIndicesTexture();

	m_TextureSkyGradient = skyBox.getTextureSkyGradient();
	m_TextureCubeNightSky = skyBox.getTextureNightSky();
	m_TextureSun = skyBox.getTextureSun();
	m_TextureMoon = skyBox.getTextureMoon();

	for (int i = 0; i < vertecies.size(); ++i) {
		m_Buffer[i].vertex = vertecies[i];
		m_Buffer[i].textureId = (i < 8 ? 0.0f : (i < 11 ? 1.0f : 2.0f));
	}

	for (int i = 0; i < indicesVertex.size(); ++i) {
		m_Buffer[indicesVertex[i]].texture = textures[indicesTexture[i]];
		m_IndexBuffer[i] = indicesVertex[i];
	}
	/*for (SkyBoxVertexData& v : vertices) {
		*m_Buffer = v;
		++m_Buffer;
	}

	for (unsigned int i : indices) {
		*m_IndexBuffer = i;
		++m_IndexBuffer;
	}*/

	m_IndexCount = indicesVertex.size();

	end();
}

void SkyBoxRenderEngine::flush() {
	glActiveTexture(GL_TEXTURE0);
	if(m_TextureSkyGradient!=nullptr) m_TextureSkyGradient->bind();
	glActiveTexture(GL_TEXTURE1);
	if (m_TextureCubeNightSky != nullptr) m_TextureCubeNightSky->bind();
	glActiveTexture(GL_TEXTURE2);
	if (m_TextureSun != nullptr) m_TextureSun->bind();
	glActiveTexture(GL_TEXTURE3);
	if (m_TextureMoon != nullptr) m_TextureMoon->bind();

	bindVAO();
	bindIBO();
	disableDepth();

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

	enableDepth();
	bindIBO();
	unbindVAO();
}