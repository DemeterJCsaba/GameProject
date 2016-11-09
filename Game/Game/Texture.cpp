#include "Texture.h"

Texture::Texture(const string filename):
	m_Name(filename)
{
	m_Pixels = LoadImage(filename.c_str(), &m_Width, &m_Height, &m_Bits);

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	switch (m_Bits) {
	case 24:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, m_Pixels);
		break;
	case 32:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_Pixels);
		break;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	delete m_Pixels;
}

void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}