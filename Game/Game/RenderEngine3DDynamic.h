#pragma once

#include <vector>

#include "RenderEngine3D.h"

using namespace std;

class RenderEngine3DDynamic : private RenderEngine3D {
private:
	vector<RawModel3D*> m_Models;
public:
	RenderEngine3DDynamic(bool disableDepth = false, int maxVertexSize = 3000);
	void submit(RawModel3D* model);
	void flush();
};