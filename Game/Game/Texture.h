#ifndef TEXTURE_H
#define TEXTURE_H

#include <GLEW\glew.h>
#include <string>
#include <map>

using namespace std;

class Texture {
protected:
	static map<string, Texture*> m_Textures;
public:
	static void clearTextures();
	static void deleteTexture(string name);

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

#endif // !TEXTURE_H