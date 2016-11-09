#include "CubeTexture.h"

CubeTexture::CubeTexture(const char* filename) {
	string dir = "Resources\\Images\\CubeTextures\\";
	string ext = ".png";
	m_FileName[0] = dir + string(filename) + "Right" + ext;
	m_FileName[1] = dir + string(filename) + "Left" + ext;
	m_FileName[2] = dir + string(filename) + "Top" + ext;
	m_FileName[3] = dir + string(filename) + "Bottom" + ext;
	m_FileName[4] = dir + string(filename) + "Back" + ext;
	m_FileName[5] = dir + string(filename) + "Front" + ext;

	unsigned int bits;
	BYTE* pixels1 = LoadImage(m_FileName[0].c_str(), &m_Width, &m_Height, &bits);
	BYTE* pixels2 = LoadImage(m_FileName[1].c_str(), &m_Width, &m_Height, &bits);
	BYTE* pixels3 = LoadImage(m_FileName[2].c_str(), &m_Width, &m_Height, &bits);
	BYTE* pixels4 = LoadImage(m_FileName[3].c_str(), &m_Width, &m_Height, &bits);
	BYTE* pixels5 = LoadImage(m_FileName[4].c_str(), &m_Width, &m_Height, &bits);
	BYTE* pixels6 = LoadImage(m_FileName[5].c_str(), &m_Width, &m_Height, &bits);
	if (pixels1 == nullptr || pixels2 == nullptr || pixels3 == nullptr || pixels4 == nullptr || pixels5 == nullptr || pixels6 == nullptr) {
		// Todo : Exception
		return;
	}

	glGenTextures(1, &m_TextureID);
	bind();

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels4);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels3);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels5);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels6);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unbind();
}

CubeTexture::~CubeTexture() {

}

void CubeTexture::bind() const {
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
}

void CubeTexture::unbind() const {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}