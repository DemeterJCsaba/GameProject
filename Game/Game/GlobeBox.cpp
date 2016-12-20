#include "GlobeBox.h"

GlobeBox::GlobeBox(vec3* pos, float d):m_Pos(pos),m_Distance(d){}

GlobeBox::~GlobeBox()
{
	delete m_Pos;
}

bool GlobeBox::isColide(CollisionBox * other)
{
	if (other->isInShape(*m_Pos)) {
		return true;
	}
	for (float i = 0; i <= 360.0; i += 45.0) {
		for (float j = 0; j <= 360.0; j += 45.0) {
			if (other->isInShape(
				vec3(
					m_Distance*sin(i)*cos(j),
					m_Distance*sin(i)*sin(j),
					m_Distance*cos(i)
				) + *m_Pos)) 
			{
				return true;
			}
		}
	}
	return false;
}

bool GlobeBox::isInShape(vec3 point)
{
	vec3 temp = point - *m_Pos;
	float possibile = sqrtf(temp.x*temp.x + temp.y*temp.y*temp.z*temp.z);
	if (possibile < m_Distance) {
		return true;
	}
	return false;
}
