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

void RenderEngine3DDynamic::submit(RawModel3D* entity) {
	m_Entities.push_back(entity);
}

void RenderEngine3DDynamic::flush(vec2 pos) {
	begin();
	for (RawModel3D* e : m_Entities) {
		vector<vec3>& vertices = e->getVertices();
		vector<vec3>& normals = e->getNormals();
		vector<vec3>& colors = e->getColors();
		vector<unsigned int>& indicesVertex = e->getIndicesVertex();
		vector<unsigned int>& indicesNormal = e->getIndicesNormal();
		vector<unsigned int>& indicesColor = e->getIndicesColor();

		vec3 pos = e->getPosition();
		vec3 rot = e->getRotation();
		mat4 matrix = mat4::translation(pos.x, pos.y, pos.z)*mat4::rotation(rot.x, 1, 0, 0)*mat4::rotation(rot.y, 0, 1, 0)*mat4::rotation(rot.z, 0, 0, 1);
		
		for (int i = 0; i < vertices.size(); ++i) {
			m_Buffer[i].vertex = matrix*vertices[i];
		}

		for (int i = 0; i < indicesVertex.size(); ++i) {
			int ind = indicesVertex[i];
			ind = ind < 0 ? 0 : ind;
			ind = ind >= vertices.size() ? vertices.size() - 1 : ind;
			m_IndexBuffer[i] = m_VertexCount + ind;
			m_Buffer[ind].normal = normals[ind];;// normals[indicesNormal[i]];
			m_Buffer[ind].color = vec3(1.0f, 0.0f, 1.0f);// colors[indicesColor[i]];
		}

		m_Buffer += vertices.size();
		m_VertexCount += (int)vertices.size();

		m_IndexBuffer += indicesVertex.size();
		m_IndexCount += (int)indicesVertex.size();
	}
	end();

	bindVAO();
	bindIBO();

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

	bindIBO();
	unbindVAO();
}