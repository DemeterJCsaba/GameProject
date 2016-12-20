#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <list>

#include "Event.h"

using namespace std;

class EventListener {
protected:
	list<Event*> m_Events;
public:
	void addEvent(Event* event) {m_Events.push_back(event);}
};

#endif // !EVENTLISTENER_H

