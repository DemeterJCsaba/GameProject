#pragma once

#include <GLEW\glew.h>
#include <string>
#include <iostream>

#include "ImageLoader.h"

using namespace std;

class CubeTexture {
private:
	GLuint m_TextureID;
	string m_Name;
	string m_FileName[6];

	unsigned int m_Width;
	unsigned int m_Height;
	unsigned int m_Bits;
public:
	CubeTexture(string filename);
	~CubeTexture();

	void bind() const;
	void unbind() const;

	const string& getName() const { return m_Name; }
};