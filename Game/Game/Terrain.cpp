#include "Terrain.h"

// static
float Terrain::getHeight(int seed, float x, float z) {
	x = x < 0 ? -x : x;
	z = z < 0 ? -z : z;
	float l1 = getInterpolatedNoise(seed,x / 32.0f, z / 32.0f)*256.0f;
	float l2 = getInterpolatedNoise(seed,x / 8.0f, z / 8.0f)*64.0f;
	float l3 = getInterpolatedNoise(seed,x / 2.0f, z / 2.0f)*16.0f;
	return l1 + l2 + l3;
}

float Terrain::getNoise(int seed, int x, int z) {
	srand(seed + x * 4691 + z * 8542);
	return ((rand() % 1000) / 499.5f) - 1.0f;
}

float Terrain::getSmoothNoise(int seed, int x, int z) {
	float corners = (getNoise(seed,x - 1, z - 1) + getNoise(seed,x + 1, z - 1) + getNoise(seed,x - 1, z + 1) + getNoise(seed,x + 1, z + 1)) / 16.0f;
	float sides = (getNoise(seed,x - 1, z) + getNoise(seed,x + 1, z) + getNoise(seed,x, z - 1) + getNoise(seed,x, z + 1)) / 8.0f;
	float center = getNoise(seed,x, z) / 4.0f;
	return corners + sides + center;
}

float Terrain::interpolate(int seed, float a, float b, float blend) {
	double theta = blend * PI;
	float f = (float)(1.0f - cos(theta))*0.5f;
	return a*(1.0f - f) + b*f;
}

float Terrain::getInterpolatedNoise(int seed, float x, float z) {
	int intX = (int)x;
	int intZ = (int)z;
	float fracX = x - intX;
	float fracZ = z - intZ;

	float v1 = getSmoothNoise(seed,intX, intZ);
	float v2 = getSmoothNoise(seed,intX + 1, intZ);
	float v3 = getSmoothNoise(seed,intX, intZ + 1);
	float v4 = getSmoothNoise(seed,intX + 1, intZ + 1);

	float i1 = interpolate(seed,v1, v2, fracX);
	float i2 = interpolate(seed,v3, v4, fracX);
	return interpolate(seed,i1, i2, fracZ);
}

vec3 Terrain::getColor(vec3 a, vec3 b, vec3 c,vec3 norm) {
	float tmp = (norm.y*8.0f - 6.5f);
	tmp = tmp < 0 ? 0 : (tmp>1 ? 1 : tmp);
	return a.y>50.0f ? vec3(1, 1, 1) : (a.y>30.0f ? vec3(0.5f, 0.5f, 0.5f) : (vec3::mix(vec3(0.2705, 0.545, 0.0), vec3(0.2851f, 0.1914f, 0.1093f), tmp)));
}



Terrain::Terrain(int x, int z,int seed, unsigned int size,unsigned int blockSize):
	m_Seed(seed),
	m_Size(size>1?size:1),
	m_BlockSize(blockSize)
{
	float** heightsBuffer = new float*[m_BlockSize + 1];
	for (int i = 0; i <= m_BlockSize; ++i) heightsBuffer[i] = new float[m_BlockSize + 1];

	int n1 = x*m_BlockSize;
	int n2 = z*m_BlockSize;

	for (int i = 0; i <= m_BlockSize; ++i)
		for (int j = 0; j <= m_BlockSize; ++j)
			heightsBuffer[i][j] = getHeight(m_Seed, i + n1, j + n2);
	
	int indexCount = 0;
	int indexCount2 = 0;
	for (int i = 0; i < m_BlockSize; ++i) {
		for (int j = 0; j < m_BlockSize; ++j) {
			int posi = i + n1;
			int posj = j + n2;
			vec3 a = vec3(posi*m_Size,       heightsBuffer[i][j],         posj*m_Size);
			vec3 b = vec3(posi*m_Size,       heightsBuffer[i][j + 1],     (posj + 1)*m_Size);
			vec3 c = vec3((posi + 1)*m_Size, heightsBuffer[i + 1][j + 1], (posj + 1)*m_Size);
			vec3 d = vec3((posi + 1)*m_Size, heightsBuffer[i + 1][j],     posj*m_Size);

			if ((i + j) % 2) {
				m_Vertices.push_back(a);
				m_Vertices.push_back(b);
				m_Vertices.push_back(c);
				
				m_Vertices.push_back(a);
				m_Vertices.push_back(c);
				m_Vertices.push_back(d);

				vec3 norm1 = norm(a, b, c);
				vec3 norm2 = norm(a, c, d);
				norm1.normalize();
				norm2.normalize();
				m_Normals.push_back(norm1);
				m_Normals.push_back(norm2);

				m_Colors.push_back(getColor(a, b, c, norm1));
				m_Colors.push_back(getColor(c, d, a, norm2));
			}
			else {
				m_Vertices.push_back(b);
				m_Vertices.push_back(c);
				m_Vertices.push_back(d);

				m_Vertices.push_back(b);
				m_Vertices.push_back(d);
				m_Vertices.push_back(a);

				vec3 norm1 = norm(b, c, d);
				vec3 norm2 = norm(b, d, a);
				norm1.normalize();
				norm2.normalize();
				m_Normals.push_back(norm1);
				m_Normals.push_back(norm2);

				m_Colors.push_back(getColor(b, c, d, norm1));
				m_Colors.push_back(getColor(d, a, b, norm2));
			}

			int indV[] = { 0,2,1,3,5,4 };
			int indN[] = { 0,0,0,1,1,1 };
			int indC[] = { 0,0,0,1,1,1 };
			for (int k = 0; k < 6; ++k) {
				m_IndicesVertex.push_back(indexCount + indV[k]);
				m_IndicesNormal.push_back(indexCount2 + indN[k]);
				m_IndicesColor.push_back(indexCount2 + indC[k]);
			}
			indexCount += 6;
			indexCount2 += 2;
		}
	}


	for (int i = 0; i <= m_BlockSize; ++i) delete heightsBuffer[i];
	delete heightsBuffer;
}

Terrain::~Terrain() {

}

