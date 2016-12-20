#pragma once
#include"vec3.h"
class CollisionBox
{
private:
protected:
public:
	virtual bool isColide(CollisionBox* other) = 0;
	virtual bool isInShape(vec3 point) = 0;
};

