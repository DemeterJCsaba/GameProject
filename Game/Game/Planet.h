#pragma once

#include "RawModel3DTextured.h"
#include "Texture2D.h"

class Planet : public RawModel3DTextured{
private:
	float m_Size;

public:
	Planet(Texture2D* texture,float distance,vec3 orbit,float size);

	float getSize() const { return m_Size; }
};