#ifndef KEYBOARDBUTTONEVENT_H
#define KEYBOARDBUTTONEVENT_H

#include <string>

#include "Event.h"

using namespace std;

class KeyboardButtonEvent : public Event {
private:
	unsigned int m_KeyCode;
	unsigned int m_ActionCode;
public:
	KeyboardButtonEvent(unsigned int keyCode,unsigned int actionCode);

	unsigned int getKeyCode() const { return m_KeyCode; }
	unsigned int getActionCode() const { return m_ActionCode; }
};

#endif // !KEYBOARDBUTTONEVENT_H
