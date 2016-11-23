#pragma once

#include<vector>

#include"VertexData.h"
#include"Texture.h"
#include"vec3.h"


class RawModel
{
private://adatatg

public:
	std::vector<VertexData3D> vertices;
	std::vector<unsigned int> indices;
private://metodus

public:
	RawModel();
	~RawModel();
};

