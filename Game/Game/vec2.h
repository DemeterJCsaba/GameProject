#pragma once

struct vec2{
	float x;
	float y;

	vec2();
	vec2(const float& x, const float& y);

	friend vec2 operator+(const vec2& left, const vec2& right);
	friend vec2 operator-(const vec2& left, const vec2& right);

	vec2& operator+=(const vec2& other);
	vec2& operator-=(const vec2& other);

	bool operator==(const vec2& other);
	bool operator!=(const vec2& other);
};

