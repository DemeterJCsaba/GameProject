#include "SquereBox.h"


SquereBox::SquereBox(vec3 * pos, vec3 * rot, int d):m_Pos(pos),m_Rot(rot),m_Distance(d){}

SquereBox::~SquereBox()
{
	delete m_Pos;
	delete m_Rot;
}

bool SquereBox::isColide(CollisionBox * other)
{
	if (other->isInShape(vec3(m_Distance, m_Distance, m_Distance) + *m_Pos) || 
		other->isInShape(vec3(-m_Distance, m_Distance, m_Distance) + *m_Pos) ||
		other->isInShape(vec3(m_Distance, -m_Distance, m_Distance) + *m_Pos) ||
		other->isInShape(vec3(m_Distance, m_Distance, -m_Distance) + *m_Pos) ||
		other->isInShape(vec3(-m_Distance, -m_Distance, m_Distance) + *m_Pos) ||
		other->isInShape(vec3(-m_Distance, m_Distance, -m_Distance) + *m_Pos) ||
		other->isInShape(vec3(m_Distance, -m_Distance, -m_Distance) + *m_Pos) ||
		other->isInShape(vec3(-m_Distance, -m_Distance, -m_Distance) + *m_Pos) ||
		other->isInShape(*m_Pos)) 
	{
		return true;
	}
	return false;
}

bool SquereBox::isInShape(vec3 point)
{
	vec3 temp = point - *m_Pos;
	float possibile = sqrtf(temp.x*temp.x+temp.y*temp.y*temp.z*temp.z);
	if (possibile < m_Distance) {
		temp.x = temp.x * cos(-m_Rot->z) - temp.y*sin(-m_Rot->z);
		temp.y = temp.x * sin(-m_Rot->z) + temp.y*cos(-m_Rot->z);

		temp.y = temp.y * cos(-m_Rot->x) - temp.z*sin(-m_Rot->x);
		temp.z = temp.y * sin(-m_Rot->x) + temp.z*cos(-m_Rot->x);

		temp.z = temp.z * cos(-m_Rot->y) - temp.x*sin(-m_Rot->y);
		temp.x = temp.z * sin(-m_Rot->y) + temp.x*cos(-m_Rot->y);

		if (fabsf(temp.x) <= m_Distance && fabsf(temp.y) <= m_Distance && fabsf(temp.z) <= m_Distance) {
			return true;
		}
	}
	return false;
}
