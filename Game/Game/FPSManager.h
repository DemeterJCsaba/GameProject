#pragma once

#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>

#include <string>
#include <map>

using namespace std;

class FPSManager {
private:
	static FPSManager INSTANCE;
public:
	static FPSManager& getInstance();

private:
	int m_FPS;
	const int SEC;
	
	float m_AverageFrameTimeMilliseconds;

	clock_t m_BeginFrame;
	clock_t m_EndFrame;
	clock_t m_DeltaTime;
	
	clock_t m_DeltaTimeForFrameCount;
	unsigned int m_FrameCount;

	map<string, chrono::steady_clock::time_point> startTime;
	map<string, chrono::duration<double, std::milli>> elapsedTime;
	
	FPSManager(int FPS);
public:
	void begin();
	void end();

	void start(string name);
	void stop(string name);
};