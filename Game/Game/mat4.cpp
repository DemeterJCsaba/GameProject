#include "mat4.h"

float toRadian(float angle){
	return angle*PI / 180;
}

mat4::mat4()
{
	for (int i = 0; i < 16; ++i)
		elements[i] = 0;
}

mat4::mat4(float diagonal)
{
	for (int i = 0; i < 16; ++i)
		elements[i] = 0;

	elements[0] = elements[5] = elements[10] = elements[15] = diagonal;
}

mat4 operator+(const mat4& left, const mat4& right)
{
	mat4 result;
	int ind;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			ind = i * 4 + j;
			result.elements[ind] = left.elements[ind] + right.elements[ind];
		}
	}
	return result;
}

mat4 operator-(const mat4& left, const mat4& right)
{
	mat4 result;
	int ind;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			ind = i * 4 + j;
			result.elements[ind] = left.elements[ind] - right.elements[ind];
		}
	}
	return result;
}

mat4 operator*(const mat4& left, const mat4& right)
{
	mat4 result;
	float sum;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			sum = 0;
			for (int k = 0; k < 4; ++k){
				sum += left.elements[i * 4 + k] * right.elements[k * 4 + j];
			}
			result.elements[i * 4 + j] = sum;
		}
	}
	return result;
}

mat4& mat4::operator+=(const mat4& other)
{
	int ind;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			ind = i * 4 + j;
			elements[ind] += other.elements[ind];
		}
	}
	return *this;
}

mat4& mat4::operator-=(const mat4& other)
{
	int ind;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			ind = i * 4 + j;
			elements[ind] -= other.elements[ind];
		}
	}
	return *this;
}

mat4& mat4::operator*=(const mat4& other)
{
	mat4 temp;
	float sum;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			sum = 0;
			for (int k = 0; k < 4; ++k){
				sum += elements[i * 4 + k] * other.elements[k * 4 + j];
			}
			temp.elements[i * 4 + j] = sum;
		}
	}
	int ind;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			ind = i * 4 + j;
			elements[ind] = temp.elements[ind];
		}
	}
	return *this;
}

mat4 mat4::identity()
{
	mat4 result;
	result.elements[0] = 1;
	result.elements[5] = 1;
	result.elements[10] = 1;
	result.elements[15] = 1;
	return result;
}

mat4 mat4::orthographic(float left, float right, float top, float bottom, float near, float far)
{
	mat4 result;

	float rl = right - left;
	float tb = top - bottom;
	float fn = far - near;

	result.elements[0] = 2 / rl;
	result.elements[5] = 2 / tb;
	result.elements[10] = -2 / fn;
	result.elements[15] = 1;

	result.elements[3] = (right + left) / rl;
	result.elements[7] = (top + bottom) / tb;
	result.elements[11] = (far + near) / fn;

	return result;
}

mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
{
	mat4 result;

	float q = 1.0 / tan(toRadian(fov) / 2);
	float a = q / aspectRatio;

	float nf = near - far;

	result.elements[0] = a;
	result.elements[5] = q;
	result.elements[10] = (near + far) / nf;
	result.elements[11] = (2 * near*far) / nf;
	result.elements[15] = 1;
	result.elements[14] = -1;

	return result;
}

mat4 mat4::translation(float x, float y, float z)
{
	mat4 result;

	result.elements[0] = 1;
	result.elements[5] = 1;
	result.elements[10] = 1;
	result.elements[15] = 1;

	result.elements[3] = x;
	result.elements[7] = y;
	result.elements[11] = z;

	return result;
}

mat4 mat4::scale(float x, float y, float z)
{
	mat4 result;

	result.elements[0] = x;
	result.elements[5] = y;
	result.elements[10] = z;
	result.elements[15] = 1;

	return result;
}

mat4 mat4::rotation(float angle, float x, float y, float z)
{
	mat4 result;

	float r = toRadian(angle);
	float s = sin(r);
	float c = cos(r);
	float omc = 1 - c;

	float xy = x*y;
	float xz = x*z;
	float yz = y*x;

	float xs = x*s;
	float ys = y*s;
	float zs = z*s;

	result.elements[0] = x*x*omc + c;
	result.elements[1] = xy*omc - zs;
	result.elements[2] = xz*omc + ys;

	result.elements[4] = xy*omc + zs;
	result.elements[5] = y*y*omc + c;
	result.elements[6] = yz*omc - xs;

	result.elements[8] = xz*omc - ys;
	result.elements[9] = yz*omc + xs;
	result.elements[10] = z*z*omc + c;

	result.elements[15] = 1;

	return result;
}

// Vector

vec3 operator*(const mat4& left, const vec3& right)
{
	vec3 result;
	result.x = left.elements[0] * right.x + left.elements[1] * right.y + left.elements[2] * right.z + left.elements[3];
	result.y = left.elements[4] * right.x + left.elements[5] * right.y + left.elements[6] * right.z + left.elements[7];
	result.z = left.elements[8] * right.x + left.elements[9] * right.y + left.elements[10] * right.z + left.elements[11];
	return result;
}
