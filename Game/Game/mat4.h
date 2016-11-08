#pragma once

#include <math.h>
#include "Maths.h"

float toRadian(float angle);

struct mat4{
	float elements[16];

	mat4();
	mat4(float diagonal);

	friend mat4 operator-(const mat4& left, const mat4& right);
	friend mat4 operator*(const mat4& left, const mat4& right);
	friend mat4 operator+(const mat4& left, const mat4& right);

	friend vec3 operator*(const mat4& left, const vec3& right);

	mat4& operator+=(const mat4& other);
	mat4& operator-=(const mat4& other);
	mat4& operator*=(const mat4& other);

	static mat4 identity();
	static mat4 orthographic(float left, float right, float top, float bottom, float near, float far);
	static mat4 perspective(float fov, float aspectRatio, float near, float far);

	static mat4 translation(float x, float y, float z);
	static mat4 rotation(float angle, float x, float y, float z);
	static mat4 scale(float x, float y, float z);
};

