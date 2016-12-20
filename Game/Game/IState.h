#ifndef ISTATE_H
#define ISTATE_H

#include <list>

#include "Event.h"

using namespace std;

class IState {
protected:
	list<Event*> m_Events;
public:
	void addEvent(Event* event) {
		m_Events.push_back(event);
	}

public:
	virtual ~IState() {}
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void resume() = 0;
	virtual void pause() = 0;
};

#endif // !ISTATE_H