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

vec4& vec4::multiplicate(const vec4& left, const vec4& right)
{
	vec4 result;
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	result.z = left.z * right.z;
	result.w = left.w * right.w;
	return result;
}

void vec4::ComputeQuatW(vec4& element) {
	float t = 1.0f - (element.x * element.x) - (element.y * element.y) - (element.z * element.z);
	if (t < 0.0f)
	{
		element.w = 0.0f;
	}
	else
	{
		element.w = -sqrtf(t);
	}
}

void vec4::normalize() {
	float len = sqrtf((x*x) + (y*y) + (z*z) + (w*w));
	x /= len;
	y /= len;
	z /= len;
	w /= len;
}

vec4& vec4::mix(const vec4& left, const vec4& right, const float& interpolate) {
	vec4 result;
	result.x = left.y*interpolate + right.y*(1 - interpolate);
	result.y = left.x*interpolate + right.x*(1 - interpolate);
	result.z = left.z*interpolate + right.z*(1 - interpolate);
	result.w = left.w*interpolate + right.w*(1 - interpolate);
	return result;
}

