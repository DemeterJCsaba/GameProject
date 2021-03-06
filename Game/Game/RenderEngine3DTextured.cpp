#include "RenderEngine3DTextured.h"

RenderEngine3DTextured::RenderEngine3DTextured(bool disableDepth, int maxVertexSize) :
	RenderEngine(),
	m_MaxVertexSize(maxVertexSize),
	m_DisableDepth(disableDepth)
{
	bindVAO();
	bindVBO();
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData3DTextured)*m_MaxVertexSize, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(VERTEX_INDEX);
	glEnableVertexAttribArray(NORMAL_INDEX);
	glEnableVertexAttribArray(TEXTURE_INDEX);
	glEnableVertexAttribArray(TEXTUREID_INDEX);

	glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData3DTextured), (const GLvoid*)(offsetof(VertexData3DTextured, VertexData3DTextured::vertex)));
	glVertexAttribPointer(NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData3DTextured), (const GLvoid*)(offsetof(VertexData3DTextured, VertexData3DTextured::normal)));
	glVertexAttribPointer(TEXTURE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData3DTextured), (const GLvoid*)(offsetof(VertexData3DTextured, VertexData3DTextured::texture)));
	glVertexAttribPointer(TEXTUREID_INDEX, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData3DTextured), (const GLvoid*)(offsetof(VertexData3DTextured, VertexData3DTextured::tetureId)));
	unbindVBO();

	bindIBO();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_MaxVertexSize*3, NULL, GL_DYNAMIC_DRAW);
	unbindIBO();
	unbindVAO();
}

void RenderEngine3DTextured::begin() {
	bindVBO();
	m_VertexBuffer = (VertexData3DTextured*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	bindIBO();
	m_IndexBuffer = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

	m_IndexCount = 0;
	m_VertexCount = 0;
	m_Textures.clear();
}

void RenderEngine3DTextured::end() {
	glUnmapBuffer(GL_ARRAY_BUFFER);
	unbindVBO();

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	unbindIBO();
}

void RenderEngine3DTextured::submit(RawModel3DTextured& model) {
	vector<vec3>& vertices = model.getVertices();
	vector<vec3>& normals = model.getNormals();
	vector<vec2>& textures = model.getTextures();
	vector<unsigned int>& indicesVertex = model.getIndicesVertex();
	vector<unsigned int>& indicesNormal = model.getIndicesNormal();
	vector<unsigned int>& indicesTexture = model.getIndicesTexture();

	vec3 pos = model.getPosition();
	vec3 rot = model.getRotation();
	mat4 matrix = mat4::translation(pos.x, pos.y, pos.z)*mat4::rotation(rot.x, 1, 0, 0)*mat4::rotation(rot.y, 0, 1, 0)*mat4::rotation(rot.z, 0, 0, 1);

	int texId = addTexture(model.getTexture());

	for (int i = 0; i < vertices.size(); ++i) {
		m_VertexBuffer[i].vertex = matrix*vertices[i];
		m_VertexBuffer[i].tetureId = texId;
	}

	for (int i = 0; i < indicesVertex.size(); ++i) {
		m_IndexBuffer[i] = m_VertexCount + indicesVertex[i];
		m_VertexBuffer[indicesVertex[i]].normal = normals[indicesNormal[i]];
		m_VertexBuffer[indicesVertex[i]].texture = textures[indicesTexture[i]];
	}

	m_VertexBuffer += vertices.size();
	m_VertexCount += (int)vertices.size();

	m_IndexBuffer += indicesVertex.size();
	m_IndexCount += (int)indicesVertex.size();
}

int RenderEngine3DTextured::addTexture(Texture* texture) {
	if (texture != nullptr) {
		m_Textures.push_back(texture);
		return (int)m_Textures.size();
	}
	return 0;
}

void RenderEngine3DTextured::flush() {
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