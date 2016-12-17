#ifndef MOVABLE_H
#define MOVABLE_H

#include "RawModel3D.h"

class Movable : public RawModel3D {
private:
	vec3 m_Motion;
	vec3 m_Rotate;
public:
	void setMotion(vec3 motion) { m_Motion = motion; }
	void addMotion(vec3 motion) { m_Motion += motion; }
	void setRotate(vec3 rotate) { m_Rotate = rotate; }
	void addRotate(vec3 rotate) { m_Rotate += rotate; }

	void update();
};

#endif // !MOVABLE_H
