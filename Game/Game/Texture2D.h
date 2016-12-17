#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <GLEW\glew.h>
#include <string>
#include <map>

#include "Texture.h"
#include "ImageLoader.h"

using namespace std;

class Texture2D : public Texture{
private:
	static string m_Dir;
public:
	static Texture2D* getTexture(string name);


	Texture2D(const string filename);
public:
	void bind() const;
	void unbind() const;
};

#endif // !TEXTURE2D_H