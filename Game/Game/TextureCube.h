#ifndef TEXTURECUBE_H
#define TEXTURECUBE_H

#include <GLEW\glew.h>
#include <string>
#include <map>

#include "Texture.h"
#include "ImageLoader.h"

using namespace std;

class TextureCube : public Texture {
private:
	static string m_Dir;
public:
	static TextureCube* getTexture(string name);


private:
	string m_FileName[6];

	TextureCube(string filename);
public:
	void bind() const;
	void unbind() const;
};

#endif // !TEXTURECUBE_H