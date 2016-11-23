#include "Terrain.h"

Terrain::Terrain(long long seed, unsigned int size):
	m_Seed(seed),
	m_Size(size>1?size:1)
{
	
}

Terrain::~Terrain() {

}

float Terrain::getHeight(float x, float z) {
	x = x < 0 ? -x : x;
	z = z < 0 ? -z : z;
	float l1 = getInterpolatedNoise(x / 16.0f, z / 16.0f)*256.0f;
	float l2 = getInterpolatedNoise(x / 4.0f, z / 4.0f)*32.0f;
	float l3 = getInterpolatedNoise(x / 2.0f, z / 2.0f)*8.0f;
	return l1 + l2 + l3;
}

float Terrain::getNoise(int x, int z) {
	srand(m_Seed + x * 4691 + z * 8542);
	return ((rand() % 1000) / 499.5) - 1.0f;
}

float Terrain::getSmoothNoise(int x, int z) {
	float corners = (getNoise(x - 1, z - 1) + getNoise(x + 1, z - 1) + getNoise(x - 1, z + 1) + getNoise(x + 1, z + 1)) / 16.0f;
	float sides = (getNoise(x - 1, z) + getNoise(x + 1, z) + getNoise(x, z - 1) + getNoise(x, z + 1)) / 8.0f;
	float center = getNoise(x,z) / 4.0f;
	return corners + sides + center;
}

float Terrain::interpolate(float a, float b, float blend) {
	double theta = blend * PI;
	float f = (float)(1.0f - cos(theta))*0.5f;
	return a*(1.0f - f) + b*f;
}

float Terrain::getInterpolatedNoise(float x, float z) {
	int intX = (int)x;
	int intZ = (int)z;
	float fracX = x - intX;
	float fracZ = z - intZ;

	float v1 = getSmoothNoise(intX, intZ);
	float v2 = getSmoothNoise(intX+1, intZ);
	float v3 = getSmoothNoise(intX, intZ+1);
	float v4 = getSmoothNoise(intX+1, intZ+1);

	float i1 = interpolate(v1, v2, fracX);
	float i2 = interpolate(v3, v4, fracX);
	return interpolate(i1, i2, fracZ);
}