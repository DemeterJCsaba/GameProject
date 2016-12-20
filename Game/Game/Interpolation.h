#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "Timer.h"

template <class T,class V>
class Interpolation : public Timer{
protected:
	void (T::*m_Function)(V);
	T* m_Object;

	V m_Start;
	V m_End;

	int m_CurrentTime;
	int m_EndTime;
public:
	Interpolation(T* object, void (T::*function)(V), V start, V end,int time) :
		m_Object(object),
		m_Function(function),
		m_Start(start),
		m_End(end),
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

		double theta = (m_CurrentTime*1.0f / m_EndTime) * PI;
		float interp = (float)(1.0f - cos(theta))*0.5f;
		float interp2 = 1.0f - interp;

		(m_Object->*m_Function)((m_Start*interp2 + m_End*interp));
	}
	
	void* getModelPtr() {
		return (void*)m_Object;
	}
};

#endif // !INTERPOLATION_H