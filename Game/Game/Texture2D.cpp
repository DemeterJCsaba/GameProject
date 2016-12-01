#include "Texture2D.h"

Texture2D::Texture2D(const string filename):
	Texture(filename)
{
	BYTE* m_Pixels = LoadImage(filename.c_str(), &m_Width, &m_Height, &m_Bits);

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

void Texture2D::bind() const {
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture2D::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}