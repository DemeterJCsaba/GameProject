#include "vec2.h"

vec2::vec2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

vec2::vec2(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
}

vec2 operator+(const vec2& left, const vec2& right)
{
	vec2 result;
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	return result;
}

vec2 operator-(const vec2& left, const vec2& right)
{
	vec2 result;
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	return result;
}

vec2& vec2::operator+=(const vec2& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

vec2& vec2::operator-=(const vec2& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

bool vec2::operator == (const vec2& other)
{
	return (this->x == other.x && this->y == other.y);
}

bool vec2::operator != (const vec2& other)
{
	return (this->x != other.x || this->y != other.y);
}

vec2 operator*(const vec2& left, const float& right) {
	vec2 result;
	result.x = left.x*right;
	result.y = left.y*right;
	return result;
}
