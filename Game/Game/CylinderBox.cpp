#include "CylinderBox.h"


CylinderBox::CylinderBox(vec3 *pos, vec3 *rot, float d, float h) :m_Pos(pos),m_Rot(rot), m_Distance(d), m_Height(h){}

CylinderBox::~CylinderBox()
{
	delete m_Pos;
	delete m_Rot;
}

bool CylinderBox::isColide(CollisionBox *other)
{
	for (int i = 0; i <= m_Height; i += 0.5) {
		for (int j = 0; j < 360; j += 45) {
			if (other->isInShape(
				vec3(
					m_Distance*cosf(j),
					m_Distance*sinf(j),
					i
				) + *m_Pos)) {
				return true;
			}
		}
	}
	return false;
}

bool CylinderBox::isInShape(vec3 point)
{
	vec3 temp = point - *m_Pos;
	temp.x = temp.x * cos(-m_Rot->z) - temp.y*sin(-m_Rot->z);
	temp.y = temp.x * sin(-m_Rot->z) + temp.y*cos(-m_Rot->z);

	temp.y = temp.y * cos(-m_Rot->x) - temp.z*sin(-m_Rot->x);
	temp.z = temp.y * sin(-m_Rot->x) + temp.z*cos(-m_Rot->x);

	temp.z = temp.z * cos(-m_Rot->y) - temp.x*sin(-m_Rot->y);
	temp.x = temp.z * sin(-m_Rot->y) + temp.x*cos(-m_Rot->y);

	if (temp.z >= m_Pos->z && temp.z <= m_Pos->z + m_Height) {
		float d = sqrtf(temp.x*temp.x + temp.y*temp.y);
		if (d <= m_Distance) {
			return true;
		}
	}
	return false;
}
