#ifndef EVENT_H
#define EVENT_H

#include <string>

using namespace std;

class Event {
public:
	static enum EVENTS {MOUSE_BUTTON,KEYBOARD_BUTTON};

private:
	unsigned int m_Event;
public:
	Event(unsigned int event);

	unsigned int getEvent() { return m_Event; }
};


#endif // !EVENT_H

