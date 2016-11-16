#pragma once

#include <random>

class Terrain {
private:
	unsigned int m_Size;
public:
	Terrain(unsigned int size = 5);
	~Terrain();

	float getHeight(int x,int y);
	unsigned int getSize() { return m_Size; }
};