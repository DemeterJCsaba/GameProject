#include "RenderEngine2D.h"

RenderEngine2D::RenderEngine2D() {
	bindVAO();
		bindVBO();
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, 0, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(GUI_VERTEX_INDEX);
		glEnableVertexAttribArray(GUI_TEXTURE_INDEX);
		glEnableVertexAttribArray(GUI_TEXTUREID_INDEX);
	
		glVertexAttribPointer(GUI_VERTEX_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData2D, VertexData2D::vertex)));
		glVertexAttribPointer(GUI_TEXTURE_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData2D, VertexData2D::texture)));
		glVertexAttribPointer(GUI_TEXTUREID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData2D, VertexData2D::textureId)));
		unbindVBO();
	
		bindIBO();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_INDICES_SIZE, NULL, GL_DYNAMIC_DRAW);
		unbindIBO();
	unbindVAO();
}

void RenderEngine2D::begin() {
	bindVBO();
	m_VertexBuffer = (VertexData2D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	bindIBO();
	m_IndexBuffer = (int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

	m_IndexCount = 0;
	m_VertexCount = 0;
}

void RenderEngine2D::end() {
	glUnmapBuffer(GL_ARRAY_BUFFER);
	unbindVBO();

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	unbindIBO();
}

void RenderEngine2D::submit(GUIImage& entity) {
	vector<vec2>& vertices = entity.getVertices();
	vector<vec2>& textures = entity.getTextures();
	vector<unsigned int>& indicesVertex = entity.getIndicesVertex();
	vector<unsigned int>& indicesTexture = entity.getIndicesTexture();

	Texture* texture = entity.getTexture();
	vec2 position = entity.getPosition();
	
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
	disableDepth();

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

	enableDepth();
	bindIBO();
	unbindVAO();
}