#include "TimerManeger.h"

#include <iostream>

TimerManager::TimerManager() {

}

TimerManager::~TimerManager() {
	for (list<Timer*>::iterator i = m_Timers.begin(); i != m_Timers.end(); ) {
		Timer* interp = (*i);
		m_Timers.erase(i++);
		delete interp;
	}
}

void TimerManager::addTimer(Timer* timer) {
	for (list<Timer*>::iterator i = m_Timers.begin(); i!= m_Timers.end() ; ++i) {
		if ((*i)->getModelPtr() == timer->getModelPtr()) {
			m_Timers.erase(i);
			break;
		}
	}
	m_Timers.push_back(timer);
}

void TimerManager::update() {
	for (list<Timer*>::iterator i = m_Timers.begin(); i != m_Timers.end(); ) {
		(*i)->update();
		if ((*i)->isDone()) {
			m_Timers.erase(i++);
		} else ++i;
	}
}