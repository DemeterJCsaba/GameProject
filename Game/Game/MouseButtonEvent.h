#ifndef MOUSEBUTTONEVENT_H
#define MOUSEBUTTONEVENT_H

#include <string>

#include "Event.h"

using namespace std;

class MouseButtonEvent : public Event {
private:
	unsigned int m_KeyCode;
	unsigned int m_ActionCode;
public:
	MouseButtonEvent(unsigned int keyCode,unsigned int actionCode);

	unsigned int getKeyCode() const { return m_KeyCode; }
	unsigned int getActionCode() const { return m_ActionCode; }
};

#endif // !MOUSEBUTTONEVENT_H
