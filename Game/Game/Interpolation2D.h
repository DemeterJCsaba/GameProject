#ifndef INTERPOLATION2D_H
#define INTERPOLATION2D_H

#include <list>

#include "Interpolation.h"
#include "RawModel2D.h"

using namespace std;

class Interpolation2D : public Interpolation {
private:
	RawModel2D* m_Model;

	vec2 m_StartPos;
	float m_StartRot;

	vec2 m_EndPos;
	float m_EndRot;
	
	int m_CurrentTime;
	int m_EndTime;
public:
	Interpolation2D(RawModel2D* model,int time,vec2 position,float rotation = 0.0f);

	void update();
	void* getModelPtr() { return m_Model; }
};

#endif // !IONINTERPOLATION2D_H
