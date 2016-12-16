#include "Interpolation2D.h"

#include <iostream>

Interpolation2D::Interpolation2D(RawModel2D* model, int time, vec2 position, float rotation):
	m_Model(model),
	m_EndTime(time),
	m_EndPos(position),
	m_EndRot(rotation)
{
	m_StartPos = m_Model->getPosition();
	m_StartRot = m_Model->getRotation();
	m_CurrentTime = 0;
}

void Interpolation2D::update() {
	++m_CurrentTime;

	double theta = (m_CurrentTime*1.0f / m_EndTime) * PI;
	float interp = (float)(1.0f - cos(theta))*0.5f;
	float interp2 = 1.0f - interp;

	m_Model->setPosition(m_StartPos*interp2 + m_EndPos*interp);

	if (m_CurrentTime == m_EndTime)
		m_IsDone = true;
}