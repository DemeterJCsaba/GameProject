#pragma once
#include<math.h>

struct vec4
{
	float x;
	float y;
	float z;
	float w;

	vec4();
	vec4(const float& x, const float& y, const float& z, const float& w);

	friend vec4 operator+(const vec4& left, const vec4& right);
	friend vec4 operator-(const vec4& left, const vec4& right);

	vec4& operator+=(const vec4& other);
	vec4& operator-=(const vec4& other);

	bool operator==(const vec4& other);
	bool operator!=(const vec4& other);

	static void ComputeQuatW(vec4& element);
	static vec4& multiplicate(const vec4& left, const vec4& right);
	static vec4& mix(const vec4& left, const vec4& right, const float& interpolate);
	void normalize();
};
