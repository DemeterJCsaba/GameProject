#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <list>

#include "Timer.h"

using namespace std;

class TimerManager {
private:
	list<Timer*> m_Timers;
public:
	TimerManager();
	~TimerManager();

	void addTimer(Timer* timer);
	void update();
};

#endif // !TIMERMANAGER_H