#pragma once
#include "CollisionBox.h"
class GlobeBox :
	public CollisionBox
{
private:
	vec3* m_Pos;
	float m_Distance;
public:
	GlobeBox(vec3* pos, float d);
	~GlobeBox();
	virtual bool isColide(CollisionBox* other);
	virtual bool isInShape(vec3 point);
};

