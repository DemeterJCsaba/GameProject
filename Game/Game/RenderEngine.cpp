#include "RenderEngine.h"

RenderEngine::RenderEngine() {
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
}

void RenderEngine::bindVAO() {
	glBindVertexArray(m_VAO);
}

void RenderEngine::unbindVAO() {
	glBindVertexArray(0);
}

void RenderEngine::bindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

void RenderEngine::unbindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderEngine::bindIBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
}

void RenderEngine::unbindIBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderEngine::enableDepth() {
	glEnable(GL_DEPTH_TEST);
}

void RenderEngine::disableDepth() {
	glDisable(GL_DEPTH_TEST);
}