#pragma once

#include "Maths.h"

struct VertexData2D {
	vec2 vertex;
	vec3 color;
	vec2 texture;
	float textureId;
};

struct SkyBoxVertexData {
	vec3 vertex;
	vec2 teture;
	float textureId;
};

struct VertexData3D {
	vec3 vertex;
	vec3 normal;
	vec3 color;
};