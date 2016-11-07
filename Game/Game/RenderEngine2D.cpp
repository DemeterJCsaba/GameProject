#include "RenderEngine2D.h"

RenderEngine2D::RenderEngine2D() {
	init();
}

void RenderEngine2D::init() {
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, 0, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
	glEnableVertexAttribArray(SHADER_TEXTUREID_INDEX);

	glVertexAttribPointer(SHADER_VERTEX_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData2D, VertexData2D::vertex)));
	//glVertexAttribPointer(SHADER_TEXTURE_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData2D, VertexData2D::texture)));
	glVertexAttribPointer(SHADER_TEXTURE_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData2D, VertexData2D::color)));
	glVertexAttribPointer(SHADER_TEXTUREID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData2D, VertexData2D::textureId)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_INDICES_SIZE, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void RenderEngine2D::begin() {
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	m_VertexBuffer = (VertexData2D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	m_IndexBuffer = (int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

	m_IndexCount = 0;
	m_VertexCount = 0;
}

void RenderEngine2D::submit(GUI& entity) {
	vector<VertexData2D>& vertices = entity.getVertices();
	vector<unsigned int>& indices = entity.getIndices();

	for (VertexData2D& v : vertices) {
		*m_VertexBuffer = v;
		++m_VertexBuffer;
	}

	for (unsigned int i : indices) {
		*m_IndexBuffer = m_VertexCount + i;
		++m_IndexBuffer;
	}
	m_IndexCount += indices.size();
	m_VertexCount += vertices.size();
}

void RenderEngine2D::end() {
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderEngine2D::flush() {
	/*for (int i = 0; i < textues.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textues[i]);
	}*/

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}