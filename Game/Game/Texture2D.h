#pragma once

#include <GLEW\glew.h>
#include <string>

#include "Texture.h"
#include "ImageLoader.h"

using namespace std;

class Texture2D : public Texture{
public:
	Texture2D(const string filename);
	
	void bind() const;
	void unbind() const;
};