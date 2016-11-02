#pragma once

#include <chrono>
#include <thread>

#define SEC_TO_MILISEC 1000.0

using namespace std;

class FPSManager {
private:
	int m_FPS;

	clock_t m_BeginFrame;
	clock_t m_EndFrame;
	clock_t m_DeltaTime;
	unsigned int m_FrameCount;

	bool m_EnableDelay;
	float m_AverageFrameTimeMilliseconds;
	float m_Temp;
	float m_Sleep;

	bool m_EnableLength;
public:
	FPSManager(int FPS, bool enableDelay = true, bool enableLength = false);
	void begin();
	void end();
};