#include "RenderEngine3DDynamic.h"

RenderEngine3DDynamic::RenderEngine3DDynamic() {
	bindVAO();
		bindVBO();
		glBufferData(GL_ARRAY_BUFFER, VERTEX_COUNT, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(VERTEX_INDEX);
		glEnableVertexAttribArray(NORMAL_INDEX);
		glEnableVertexAttribArray(COLOR_INDEX);

		glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData3D, VertexData3D::vertex)));
		glVertexAttribPointer(NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData3D, VertexData3D::normal)));
		glVertexAttribPointer(COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData3D, VertexData3D::color)));
		unbindVBO();

		bindIBO();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICES_COUNT, NULL, GL_DYNAMIC_DRAW);
		unbindIBO();
	unbindVAO();
}

RenderEngine3DDynamic::~RenderEngine3DDynamic() {

}

void RenderEngine3DDynamic::begin() {
	bindVBO();
	m_Buffer = (VertexData3D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	bindIBO();
	m_IndexBuffer = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

	m_IndexCount = 0;
	m_VertexCount = 0;
}

void RenderEngine3DDynamic::end() {
	glUnmapBuffer(GL_ARRAY_BUFFER);
	unbindVBO();
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	unbindIBO();
}

void RenderEngine3DDynamic::submit(RawModel<VertexData3D>* entity) {
	m_Entities.push_back(entity);
}

void RenderEngine3DDynamic::flush(vec2 pos) {
	begin();
	for (RawModel<VertexData3D>* e : m_Entities) {
		vec3 pos = e->getPosition();
		vec3 rot = e->getRotation();
		mat4 matrix = mat4::translation(pos.x, pos.y, pos.z)*mat4::rotation(rot.x, 1, 0, 0)*mat4::rotation(rot.y, 0, 1, 0)*mat4::rotation(rot.z, 0, 0, 1);
		
		for (VertexData3D& v : e->getVertices()) {
			*m_Buffer = v;
			m_Buffer->vertex = matrix*m_Buffer->vertex;
			++m_Buffer;
		}

		for (unsigned int i : e->getIndices()) {
			int ind = (i >= 0 ? i : 0);
			ind = (ind < e->getIndices().size() ? ind : 0);
			*m_IndexBuffer = m_VertexCount + ind;
			++m_IndexBuffer;
			++m_IndexCount;
		}

		m_IndexCount += e->getIndices().size();
		m_VertexCount += e->getVertices().size();
	}
	end();

	bindVAO();
	bindIBO();

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

	bindIBO();
	unbindVAO();
}