#pragma once

#include <vector>
#include "VertexData.h"

using namespace std;

class GUI {
private:
	vector<VertexData2D> m_Vertices;
	vector<unsigned int> m_Indices;
public:
	GUI();
	vector<VertexData2D>& getVertices();
	vector<unsigned int>& getIndices();
};