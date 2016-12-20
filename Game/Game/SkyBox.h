#pragma once

#include <vector>

#include "RawModel3DTextured.h"
#include "TextureCube.h"

using namespace std;

class SkyBox : public RawModel3DTextured{
private:
	float m_Size;
public:
	SkyBox(TextureCube* texture, float size = 100.0f);
	~SkyBox();

	float getSize() const { return m_Size; }
};