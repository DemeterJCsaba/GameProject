#pragma once
#include "CollisionBox.h"
class CylinderBox :
	public CollisionBox
{
private:
	vec3* m_Pos;
	vec3* m_Rot;
	float m_Distance;
	float m_Height;
public:
	CylinderBox(vec3*,vec3*,float,float);
	~CylinderBox();
	virtual bool isColide(CollisionBox*);
	virtual bool isInShape(vec3);
};

