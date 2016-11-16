#include "Terrain.h"

Terrain::Terrain(unsigned int size):
	m_Size(size>1?size:1)
{

}

Terrain::~Terrain() {

}

float Terrain::getHeight(int x, int y) {
	srand(123);
	return -3 + rand()/(RAND_MAX*1.0) ;
}