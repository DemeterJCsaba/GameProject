#include "FPSManager.h"

FPSManager& FPSManager::getInstance() {
	static FPSManager INSTANCE(60);
	return INSTANCE;
}


FPSManager::FPSManager(int FPS):
	m_FPS(FPS-1),
	SEC((chrono::duration_cast<chrono::milliseconds>(chrono::seconds(1))).count())
{
	m_DeltaTimeForFrameCount = 0;
	m_DeltaTime = 0;
	m_FrameCount = 0;

	m_AverageFrameTimeMilliseconds = SEC*1.0 / m_FPS;
}

void FPSManager::begin()
{
	m_BeginFrame = clock();
	start("Frame");
}

void FPSManager::end()
{
	stop("Frame");
	++m_FrameCount;
	m_EndFrame = clock();
	m_DeltaTime = (m_EndFrame - m_BeginFrame);

	if ((m_DeltaTimeForFrameCount+m_DeltaTime) < m_FrameCount*m_AverageFrameTimeMilliseconds) {
		this_thread::sleep_for(chrono::milliseconds((int)(m_FrameCount*m_AverageFrameTimeMilliseconds - (m_DeltaTimeForFrameCount + m_DeltaTime))));
	}

	m_EndFrame = clock();
	m_DeltaTimeForFrameCount += (m_EndFrame - m_BeginFrame);
	if (m_DeltaTimeForFrameCount >= SEC) {
		cout << "FPS: " << m_FrameCount << endl;
		m_FrameCount = 0;
		m_DeltaTimeForFrameCount -= SEC;

		double fram = elapsedTime["Frame"].count();
		for (map<string, chrono::duration<double, std::milli>>::iterator it = elapsedTime.begin(); it != elapsedTime.end(); ++it) {
			cout << setw(20)<< left << it->first << ": " << setw(10) << left << ((100.0*it->second.count())/ fram) << "% - " << it->second.count() << endl;
			it->second = chrono::duration<double, std::milli>();
		}
	}
}

void FPSManager::start(string name) {
	startTime[name] = chrono::high_resolution_clock::now();
}

void FPSManager::stop(string name) {
	elapsedTime[name] += (chrono::high_resolution_clock::now() - startTime[name]);
}