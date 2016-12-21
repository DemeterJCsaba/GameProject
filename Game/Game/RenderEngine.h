#pragma once

#include <GLEW\glew.h>

class RenderEngine {
private:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
protected:
	RenderEngine();

	void bindVAO();
	void unbindVAO();
	void bindVBO();
	void unbindVBO();
	void bindIBO();
	void unbindIBO();

	void enableDepth();
	void disableDepth();
public:
	virtual void begin() = 0;
	virtual void end() = 0;

	virtual void flush() = 0;
};