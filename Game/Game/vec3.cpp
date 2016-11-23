#include "vec3.h"

vec3::vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

vec3::vec3(const float& xyz) 
{
	x = xyz;
	y = xyz;
	z = xyz;
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
	result.y = left.y + right.y;
	result.x = left.x + right.x;
	result.z = left.z + right.z;
	return result;
}

vec3 operator-(const vec3& left, const vec3& right)
{
	vec3 result;
	result.y = left.y - right.y;
	result.x = left.x - right.x;
	result.z = left.z - right.z;
	return result;
}
vec3 operator*(const vec3& left, const vec3& right)
{
	vec3 result;
	result.y = left.y * right.y;
	result.x = left.x * right.x;
	result.z = left.z * right.z;
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

vec3& vec3::multiplicate_vec4(const vec4& left, const vec3& right) {
	vec3 result;
	result.y = left.y * right.y;
	result.x = left.x * right.x;
	result.z = left.z * right.z;
	return result;
}

vec3& vec3::mix(const vec3& left, const vec3& right, const float& interpolate) {
	vec3 result;
	result.x = left.x*interpolate + right.x*(1 - interpolate);
	result.y = left.y*interpolate + right.y*(1 - interpolate);
	result.z = left.z*interpolate + right.z*(1 - interpolate);
	return result;
}

float* vec3::value_ptr(const vec3& element) {
	float result[3];
	result[0] = element.x;
	result[1] = element.y;
	result[2] = element.z;
	return result;
}

void vec3::normalize() {
	float len = sqrtf((x*x) + (y*y) + (z*z));
	x /= len;
	y /= len;
	z /= len;
}

vec3& vec3::normalize(const vec3& obj) {
	float len = sqrtf((obj.x*obj.x) + (obj.y*obj.y) + (obj.z*obj.z));
	vec3 result;
	result.x = obj.x / len;
	result.y = obj.y / len;
	result.z = obj.z / len;
	return result;
}

vec3& vec3::cross(const vec3& left, const vec3& right) {
	vec3 result;
	result.y = (left.y + right.y) / 2;
	result.x = (left.x + right.x) / 2;
	result.z = (left.z + right.z) / 2;
	return result;
}
