#pragma once

#include<vector>

#include "Maths.h"

struct VertexData2D {
	vec2 vertex;
	vec3 color;
	vec2 texture;
	float textureId;
};

struct SkyBoxVertexData {
	vec3 vertex;
	vec2 texture;
	float textureId;

	SkyBoxVertexData(vec3 vertex, vec2 texture = vec2(), float textureId = 0.0f):
		vertex(vertex),texture(texture),textureId(textureId)
	{}
};

struct VertexData3D {
	vec3 vertex;
	vec3 normal;
	vec3 color;
};
