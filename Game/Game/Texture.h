#pragma once

#include <GLEW\glew.h>
#include <string>

#include "ImageLoader.h"

using namespace std;

class Texture {
private:
	GLuint m_TextureID;
	string m_Name;

	unsigned int m_Width;
	unsigned int m_Height;
	unsigned int m_Bits;

	BYTE* m_Pixels;
public:
	Texture(const string filename);
	~Texture();
	void bind() const;
	void unbind() const;

	GLuint getTextureID() { return m_TextureID; }
};