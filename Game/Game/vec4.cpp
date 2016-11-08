#include "vec4.h"

vec4::vec4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

vec4::vec4(const float& x, const float& y, const float& z, const float& w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

vec4 operator+(const vec4& left, const vec4& right)
{
	vec4 result;
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;
	result.w = left.w + right.w;
	return result;
}

vec4 operator-(const vec4& left, const vec4& right)
{
	vec4 result;
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;
	result.w = left.w - right.w;
	return result;
}

vec4& vec4::operator+=(const vec4& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;
	return *this;
}

vec4& vec4::operator-=(const vec4& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	this->w -= other.w;
	return *this;
}

bool vec4::operator == (const vec4& other)
{
	return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
}

bool vec4::operator != (const vec4& other)
{
	return (this->x != other.x || this->y != other.y || this->z != other.z || this->w != other.w);
}

