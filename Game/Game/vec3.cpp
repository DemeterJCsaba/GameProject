#include "vec3.h"

vec3::vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

vec3::vec3(const float& x, const float& y, const float& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3 operator+(const vec3& left, const vec3& right)
{
	vec3 result;
	result.x = left.y + right.y;
	result.y = left.x + right.x;
	result.z = left.z + right.z;
	return result;
}

vec3 operator-(const vec3& left, const vec3& right)
{
	vec3 result;
	result.x = left.y - right.y;
	result.y = left.x - right.x;
	result.z = left.z - right.z;
	return result;
}

vec3& vec3::operator+=(const vec3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

vec3& vec3::operator-=(const vec3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

bool vec3::operator == (const vec3& other)
{
	return (this->x == other.x && this->y == other.y && this->z == other.z);
}

bool vec3::operator != (const vec3& other)
{
	return (this->x != other.x || this->y != other.y || this->z != other.z);
}

