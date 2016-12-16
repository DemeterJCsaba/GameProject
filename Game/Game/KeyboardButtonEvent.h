#ifndef KEYBOARDBUTTONEVENT_H
#define KEYBOARDBUTTONEVENT_H

#include <string>

#include "Event.h"

using namespace std;

class KeyboardButtonEvent : public Event {
private:
	unsigned int m_ButtonCode;
public:
	KeyboardButtonEvent(unsigned int buttonCode);
};

#endif // !KEYBOARDBUTTONEVENT_H
