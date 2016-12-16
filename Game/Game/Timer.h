#ifndef TIMER_H
#define TIMER_H

class Timer {
protected:
	bool m_IsDone;
public:
	virtual void update() = 0;
	bool isDone() const { return m_IsDone; }
	virtual void* getModelPtr() = 0;
};

#endif // !TIMER_H

