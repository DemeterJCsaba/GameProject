#pragma once

#include "RawModel2D.h"
#include "Texture.h"

using namespace std;

class GUIImage : public RawModel2D {
protected:
	vec2 m_Size;
public:
	GUIImage(vec2 position,vec2 size, Texture* texture);

	vec2 getSize() const { return m_Size; }
};