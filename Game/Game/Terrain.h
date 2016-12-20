#pragma once

#include <random>

#include "Maths.h"
#include "RawModel3D.h"

using namespace std;

class Terrain : public RawModel3D {
private:
	static float getNoise(int seed, int x, int z);
	static float getSmoothNoise(int seed, int x, int z);
	static float interpolate(int seed, float a, float b, float blend);
	static float getInterpolatedNoise(int seed, float x, float z);
public:
	static float getHeight(int seed,float x, float z, float size);
	static vec3 getColor(vec3 a, vec3 b, vec3 c,vec3 norm);

private:
	int m_Seed;
	int m_Size;
	int m_BlockSize;
public:
	Terrain(int x,int z,int seed, unsigned int size = 5, unsigned int blockSize = 32);
	~Terrain();

	int getSize() const { return m_Size; }
	int getSeed() const { return m_Seed; }
	int getBlockSize() const { return m_BlockSize; }
};