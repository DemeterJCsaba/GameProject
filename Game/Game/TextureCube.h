#pragma once

#include <GLEW\glew.h>
#include <string>
#include <iostream>

#include "Texture.h"
#include "ImageLoader.h"

using namespace std;

class TextureCube : public Texture {
private:
	string m_FileName[6];
public:
	TextureCube(string filename);

	void bind() const;
	void unbind() const;
};