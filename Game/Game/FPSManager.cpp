#include "FPSManager.h"

FPSManager::FPSManager(int FPS, bool enableDelay, bool enableLength):
	m_FPS(FPS-1), 
	m_EnableDelay(enableDelay), 
	m_EnableLength(enableLength),
	SEC((chrono::duration_cast<chrono::milliseconds>(chrono::seconds(1))).count())
{
	m_DeltaTime = 0;
	m_FrameCount = 0;

	m_AverageFrameTimeMilliseconds = SEC*1.0 / m_FPS;
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
	if (m_DeltaTime >= SEC) {
#if DEBUG_MODE
		//printf("FPS: %d\n", m_FrameCount);
#endif
		m_FrameCount = 0;
		m_Temp = 0.0;
		m_DeltaTime -= CLOCKS_PER_SEC;
	}

	if (m_EnableDelay && m_DeltaTime < m_Temp) {
		m_Sleep = m_Temp - m_DeltaTime;
		this_thread::sleep_for(chrono::milliseconds((int)m_Sleep));
		m_DeltaTime += m_Sleep;
	}
}