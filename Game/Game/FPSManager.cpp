#include "FPSManager.h"

FPSManager::FPSManager(int FPS, bool enableDelay, bool enableLength)
	: m_FPS(FPS-1), m_EnableDelay(enableDelay), m_EnableLength(enableLength)
{
	m_DeltaTime = 0;
	m_FrameCount = 0;

	m_AverageFrameTimeMilliseconds = SEC_TO_MILISEC / m_FPS;
	m_Temp = 0;
}

void FPSManager::begin()
{
	m_BeginFrame = clock();
}

void FPSManager::end()
{
	m_EndFrame = clock();
	m_DeltaTime += (m_EndFrame - m_BeginFrame);
	++m_FrameCount;
	m_Temp += m_AverageFrameTimeMilliseconds;
	if (m_DeltaTime >= SEC_TO_MILISEC) {
		printf("FPS: %d\n", m_FrameCount);
		m_FrameCount = 0;
		m_Temp = 0.0;
		m_DeltaTime -= CLOCKS_PER_SEC;
	}

	if (m_EnableLength)
	{
		printf("Frame length: %.3f ms\n", (m_EndFrame - m_BeginFrame) / 1000.0);
	}

	if (m_EnableDelay && m_DeltaTime < m_Temp) {
		m_Sleep = m_Temp - m_DeltaTime;
		this_thread::sleep_for(chrono::milliseconds((int)m_Sleep));
		m_DeltaTime += m_Sleep;
	}
}