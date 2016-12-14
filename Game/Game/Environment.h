#pragma once

#include "Maths.h"

class Environment {
private:
	int m_Seed;

	float m_TimeSpeed = 0.01f;

	float m_Time;
	vec3 m_SunDirection;

	float m_Gravity;
public:
	Environment(int seed = 12345,float timeSpeed = 0.01f,float gravity = 1.0f);
	~Environment();

	void update();

	// sees
	void setSeed(int seed) { m_Seed = seed; }
	int getSeed() const { return m_Seed; }

	// time
	void setTimeSpeed(float timeSpeed) { m_TimeSpeed = timeSpeed; }
	float getTimeSpeed() const { return m_TimeSpeed; }

	void setTime(float time) { m_Time = time; }
	float getTime() const { return m_Time; }
	vec3 getSunDirection() const { return m_SunDirection; }

	// gravity
	void setGravity(float gravity) { m_Gravity = gravity; }
	float getGravity() const { return m_Gravity; }
};