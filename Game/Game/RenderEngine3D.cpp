#include "RenderEngine3D.h"

#include <iostream>

RenderEngine3D::RenderEngine3D(bool disableDepth, int maxVertexSize):
	RenderEngine(),
	m_MaxVertexSize(maxVertexSize),
	m_DisableDepth(disableDepth)
{
	bindVAO();
		bindVBO();
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData3D)*m_MaxVertexSize, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(VERTEX_INDEX);
		glEnableVertexAttribArray(NORMAL_INDEX);
		glEnableVertexAttribArray(COLOR_INDEX);

		glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (const GLvoid*)(offsetof(VertexData3D, VertexData3D::vertex)));
		glVertexAttribPointer(NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (const GLvoid*)(offsetof(VertexData3D, VertexData3D::normal)));
		glVertexAttribPointer(COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (const GLvoid*)(offsetof(VertexData3D, VertexData3D::color)));
		unbindVBO();

		bindIBO();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_MaxVertexSize*3, NULL, GL_DYNAMIC_DRAW);
		unbindIBO();
	unbindVAO();
}

void RenderEngine3D::begin() {
	bindVBO();
	m_VertexBuffer = (VertexData3D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	bindIBO();
	m_IndexBuffer = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

	m_IndexCount = 0;
	m_VertexCount = 0;
}

void RenderEngine3D::end() {
	glUnmapBuffer(GL_ARRAY_BUFFER);
	unbindVBO();

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	unbindIBO();
}

void RenderEngine3D::submit(RawModel3D* model) {
	vector<vec3>& vertices = model->getVertices();
	vector<vec3>& normals = model->getNormals();
	vector<vec3>& colors = model->getColors();
	vector<unsigned int>& indicesVertex = model->getIndicesVertex();
	vector<unsigned int>& indicesNormal = model->getIndicesNormal();
	vector<unsigned int>& indicesColor = model->getIndicesColor();

	/*if (vertices.size() == 0) vertices.push_back(vec3());
	if (normals.size() == 0) normals.push_back(vec3());
	if (colors.size() == 0) colors.push_back(vec3());
	if (indicesVertex.size() == 0) indicesVertex.push_back(0);
	if (indicesNormal.size() == 0) indicesNormal.push_back(0);
	if (indicesColor.size() == 0) indicesColor.push_back(0);*/

	vec3 pos = model->getPosition();
	vec3 rot = model->getRotation();
	vec3 sca = model->getScale();
	mat4 rotation = mat4::rotation(rot.x, 1, 0, 0)*mat4::rotation(rot.y, 0, 1, 0)*mat4::rotation(rot.z, 0, 0, 1);
	mat4 matrix = mat4::scale(sca.x,sca.y,sca.z)*mat4::translation(pos.x, pos.y, pos.z)*rotation;

	for (int i = 0; i < vertices.size(); ++i) {
		m_VertexBuffer[i].vertex = matrix*vertices[i];
	}

	for (int i = 0; i < indicesVertex.size(); ++i) {
		/*int indV = indicesVertex.size()>i?indicesVertex[i]:0;
		indV = (indV < 0 ? 0 : indV);
		indV = (indV>= vertices.size()? vertices.size()-1:indV);
		int indN = indicesNormal.size()>i ? indicesNormal[i]:0;
		indN = (indN < 0 ? 0 : indN);
		indN = (indN >= normals.size() ? normals.size() - 1 : indN);
		int indC = indicesColor.size()>i ? indicesColor[i]:0;
		indC = (indC < 0 ? 0 : indC);
		indC = (indC >= colors.size() ? colors.size() - 1 : indC);*/

		/*m_IndexBuffer[i] = m_VertexCount + indV;
		m_VertexBuffer[indV].normal = normals[indN];
		m_VertexBuffer[indV].color = colors[indC];*/
		/*int tmp = indicesVertex[i] < 0 ? 0 : indicesVertex[i];
		int tmp2 = indicesNormal[i] < 0 ? 0 : indicesNormal[i];*/
		m_IndexBuffer[i] = m_VertexCount + indicesVertex[i];
		m_VertexBuffer[indicesVertex[i]].normal = rotation*normals[indicesNormal[i]];
		m_VertexBuffer[indicesVertex[i]].color = colors[indicesColor[i]];
	}
	
	m_VertexBuffer += vertices.size();
	m_VertexCount += (int)vertices.size();

	m_IndexBuffer += indicesVertex.size();
	m_IndexCount += (int)indicesVertex.size();
}

void RenderEngine3D::flush() {
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

int RenderEngine3D::addTexture(Texture* texture) {
	if (texture != nullptr) {
		m_Textures.push_back(texture);
		return (int)m_Textures.size();
	}
	return 0;
}