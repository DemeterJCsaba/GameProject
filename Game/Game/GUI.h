#pragma once

#include <vector>
#include "VertexData.h"
#include "Texture.h"

using namespace std;

class GUI {
protected:
	vector<VertexData2D> m_Vertices;
	vector<unsigned int> m_Indices;
	Texture* m_Texture = nullptr;

	vec2 m_Position;
public:
	GUI(float x, float y);
	GUI(float x, float y,Texture* texture);

	vector<VertexData2D>& getVertices(){ return m_Vertices; }
	vector<unsigned int>& getIndices(){ return m_Indices; }
	Texture* getTexture() { return m_Texture; }
	vec2 getPosition() { return m_Position; }
private:
	void tmp();
};