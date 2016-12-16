#ifndef DELAY_H
#define DELAY_H

#include "Timer.h"

template <class T>
class Delay : public Timer {
private:
	void (T::*m_Function)();
	T* m_Object;

	int m_CurrentTime;
	int m_EndTime;
public:
	Delay(T* object, void (T::*function)(), int time) :
		m_Object(object),
		m_Function(function),
		m_EndTime(time)
	{
		m_CurrentTime = 0;
	}

	void update() {
		if (m_CurrentTime > m_EndTime) {
			m_IsDone = true;
			return;
		}
		++m_CurrentTime;
		if (m_CurrentTime == m_EndTime)
			(m_Object->*m_Function)();
	}

	void* getModelPtr() {
		return (void*)nullptr;
	}
};

#endif