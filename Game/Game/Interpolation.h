#ifndef INTERPOLATION_H
#define INTERPOLATION_H

class Interpolation {
protected:
	bool m_IsDone;
public:
	virtual void update() = 0;
	bool isDone() const { return m_IsDone; }
	virtual void* getModelPtr() = 0;
};

#endif // !INTERPOLATION_H