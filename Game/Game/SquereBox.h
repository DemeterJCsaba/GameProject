#pragma once
#include<math.h>

#include"CollisionBox.h"
#include"Maths.h"
class SquereBox :public CollisionBox
{
private:
	vec3* m_Pos;
	vec3* m_Rot;
	float m_Distance;
public:
	SquereBox(vec3* pos, vec3* rot, int d);
	~SquereBox();
	virtual bool isColide(CollisionBox* other);
	virtual bool isInShape(vec3 point);
};

