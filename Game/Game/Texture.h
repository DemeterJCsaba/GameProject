#pragma once

#include <GLEW\glew.h>
#include <string>

using namespace std;

class Texture {
protected:
	GLuint m_TextureID;
	string m_Name;

	unsigned int m_Width;
	unsigned int m_Height;
	unsigned int m_Bits;
public:
	Texture(const string filename): m_Name(filename) {}
	~Texture() { glDeleteTextures(1, &m_TextureID); }

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	const string& getName() const { return m_Name; }
};