#pragma once

#include <cstddef>
#include <GLEW\glew.h>

#include "GUI.h"

#define RENDERER_MAX_SPRITES  300000
#define RENDERER_VERTEX_SIZE  sizeof(VertexData2D)
#define RENDERER_SPRITE_SIZE  RENDERER_VERTEX_SIZE*4
#define RENDERER_BUFFER_SIZE  RENDERER_SPRITE_SIZE*RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES*6

#define SHADER_VERTEX_INDEX 0
#define SHADER_TEXTURE_INDEX  1
#define SHADER_TEXTUREID_INDEX  2

class RenderEngine2D {
private:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;

	VertexData2D* m_VertexBuffer;
	int* m_IndexBuffer;
	GLuint m_IndexCount;
	GLuint m_VertexCount;
public:
	RenderEngine2D();
	void begin();
	void submit(GUI& entity);
	void end();
	void flush();
private:
	void init();
};