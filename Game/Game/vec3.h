#pragma once

struct vec3{
	float x;
	float y;
	float z;

	vec3();
	vec3(const float& x, const float& y, const float& z);

	friend vec3 operator+(const vec3& left, const vec3& right);
	friend vec3 operator-(const vec3& left, const vec3& right);

	vec3& operator+=(const vec3& other);
	vec3& operator-=(const vec3& other);

	bool operator==(const vec3& other);
	bool operator!=(const vec3& other);
};

