#pragma once

#include <random>
#include "Maths.h"

using namespace std;

class Terrain {
private:
	long long m_Seed;
	unsigned int m_Size;
public:
	Terrain(long long seed, unsigned int size = 5);
	~Terrain();

	float getHeight(float x,float z);
	int getSize() { return m_Size; }
private:
	float getNoise(int x, int z);
	float getSmoothNoise(int x, int z);
	float interpolate(float a, float b, float blend);
	float getInterpolatedNoise(float x, float z);
};