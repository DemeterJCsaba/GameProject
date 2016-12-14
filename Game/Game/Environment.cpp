#include "Environment.h"

Environment::Environment(int seed, float timeSpeed, float gravity):
	m_Seed(seed),
	m_TimeSpeed(timeSpeed),
	m_Gravity(gravity)
{

}

Environment::~Environment() {

}

void Environment::update() {
	m_Time = m_Time + m_TimeSpeed;
	m_Time = m_Time > 360 ? m_Time - 360 : m_Time;
	m_SunDirection = vec3(0, sin(toRadian(m_Time)), cos(toRadian(m_Time)));
}