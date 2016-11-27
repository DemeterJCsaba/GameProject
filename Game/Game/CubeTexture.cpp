#include "CubeTexture.h"

CubeTexture::CubeTexture(string filename):
	m_Name(filename)
{
	int extLen = 0;
	if (filename.size()>4 && filename[filename.size() - 4] == '.') extLen = 3;
	if (filename.size()>5 && filename[filename.size() - 5] == '.') extLen = 4;
	if (extLen == 0) {
		cout << "Error: CubeTexture - file name" << endl;
	}

	string fname = filename.substr(0, filename.size() - extLen - 1);
	string ext = filename.substr(filename.size() - extLen - 1, extLen+1);

	m_FileName[0] = fname + "Right" + ext;
	m_FileName[1] = fname + "Left" + ext;
	m_FileName[2] = fname + "Top" + ext;
	m_FileName[3] = fname + "Bottom" + ext;
	m_FileName[4] = fname + "Back" + ext;
	m_FileName[5] = fname + "Front" + ext;

	unsigned int bits;
	BYTE* pixels1 = LoadImage(m_FileName[0].c_str(), &m_Width, &m_Height, &bits);
	BYTE* pixels2 = LoadImage(m_FileName[1].c_str(), &m_Width, &m_Height, &bits);
	BYTE* pixels3 = LoadImage(m_FileName[2].c_str(), &m_Width, &m_Height, &bits);
	BYTE* pixels4 = LoadImage(m_FileName[3].c_str(), &m_Width, &m_Height, &bits);
	BYTE* pixels5 = LoadImage(m_FileName[4].c_str(), &m_Width, &m_Height, &bits);
	BYTE* pixels6 = LoadImage(m_FileName[5].c_str(), &m_Width, &m_Height, &bits);
	if (pixels1 == nullptr || pixels2 == nullptr || pixels3 == nullptr || pixels4 == nullptr || pixels5 == nullptr || pixels6 == nullptr) {
		cout << "Error: CubeTexture - file format" << endl;
		return;
	}

	glGenTextures(1, &m_TextureID);
	bind();

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels3);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels4);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels5);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels6);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unbind();
}

CubeTexture::~CubeTexture() {
	glDeleteTextures(1, &m_TextureID);
}

void CubeTexture::bind() const {
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
}

void CubeTexture::unbind() const {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}