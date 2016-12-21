#ifndef MOVABLE_H
#define MOVABLE_H

#include "RawModel3D.h"

class Movable : public RawModel3D {
protected:
	vec3 m_Motion;
	vec3 m_Rotate;
public:
	Movable(vec3 postion = vec3(), vec3 rotation = vec3(), vec3 scale = vec3(1.0f)) : RawModel3D(postion,rotation,scale) {}

	void setMotion(vec3 motion) { m_Motion = motion; }
	void addMotion(vec3 motion) { m_Motion += motion; }
	void setRotate(vec3 rotate) { m_Rotate = rotate; }
	void addRotate(vec3 rotate) { m_Rotate += rotate; }

	void update();
};

#endif // !MOVABLE_H
