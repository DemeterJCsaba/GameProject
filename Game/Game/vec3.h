#pragma once
#include<math.h>

#include"vec4.h"

struct vec3{
	float x;
	float y;
	float z;

	vec3();
	vec3(const float& x, const float& y, const float& z);
	vec3(const float& xyz);

	friend vec3 operator+(const vec3& left, const vec3& right);
	friend vec3 operator-(const vec3& left, const vec3& right);
	friend vec3 operator*(const vec3& left, const vec3& right);

	vec3& operator+=(const vec3& other);
	vec3& operator-=(const vec3& other);

	bool operator==(const vec3& other);
	bool operator!=(const vec3& other);

	static vec3& multiplicate_vec4(const vec4& left, const vec3& right);
	static vec3& mix(const vec3& left, const vec3& right, const float& interpolate);
	static float* value_ptr(const vec3& element);
	void normalize();
	static vec3& normalize(const vec3& obj);
	static vec3& cross(const vec3& left, const vec3& right);
};

