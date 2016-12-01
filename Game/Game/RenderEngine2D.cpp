#include "RenderEngine2D.h"

RenderEngine2D::RenderEngine2D(bool disableDepth, int maxVertexSize):
	m_MaxVertexSize(maxVertexSize),
	m_DisableDepth(disableDepth)
{
	bindVAO();
		bindVBO();
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData2D)*m_MaxVertexSize, 0, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(VERTEX_INDEX);
		glEnableVertexAttribArray(TEXTURE_INDEX);
		glEnableVertexAttribArray(TEXTUREID_INDEX);
	
		glVertexAttribPointer(VERTEX_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData2D), (const GLvoid*)(offsetof(VertexData2D, VertexData2D::vertex)));
		glVertexAttribPointer(TEXTURE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData2D), (const GLvoid*)(offsetof(VertexData2D, VertexData2D::texture)));
		glVertexAttribPointer(TEXTUREID_INDEX, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData2D), (const GLvoid*)(offsetof(VertexData2D, VertexData2D::textureId)));
		unbindVBO();
	
		bindIBO();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_MaxVertexSize*3, NULL, GL_DYNAMIC_DRAW);
		unbindIBO();
	unbindVAO();
}

void RenderEngine2D::begin() {
	bindVBO();
	m_VertexBuffer = (VertexData2D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	bindIBO();
	m_IndexBuffer = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

	m_IndexCount = 0;
	m_VertexCount = 0;
	m_Textures.clear();
}

void RenderEngine2D::end() {
	glUnmapBuffer(GL_ARRAY_BUFFER);
	unbindVBO();

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	unbindIBO();
}

void RenderEngine2D::submit(RawModel2D& model) {
	vector<vec2>& vertices = model.getVertices();
	vector<vec2>& textures = model.getTextures();
	vector<unsigned int>& indicesVertex = model.getIndicesVertex();
	vector<unsigned int>& indicesTexture = model.getIndicesTexture();

	Texture* texture = model.getTexture();
	vec2 position = model.getPosition();
	
	int texId = 0;
	if (texture != nullptr) {
		m_Textures.push_back(texture);
		texId = (int)m_Textures.size();
	}

	for (int i = 0; i < vertices.size(); ++i) {
		m_VertexBuffer[i].vertex = vertices[i];
		m_VertexBuffer[i].vertex += position;
		m_VertexBuffer[i].textureId = (float)texId;
	}

	for (int i = 0; i < indicesVertex.size(); ++i) {
		m_IndexBuffer[i] = m_VertexCount + indicesVertex[i];
		m_VertexBuffer[indicesVertex[i]].texture = textures[indicesTexture[i]];
	}

	m_VertexBuffer += vertices.size();
	m_VertexCount += (int)vertices.size();

	m_IndexBuffer += indicesVertex.size();
	m_IndexCount += (int)indicesVertex.size();
}

void RenderEngine2D::flush() {
	for (int i = 0; i < m_Textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		m_Textures[i]->bind();
	}

	bindVAO();
	bindIBO();
	if (m_DisableDepth) disableDepth();

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

	if (m_DisableDepth) enableDepth();
	bindIBO();
	unbindVAO();
}