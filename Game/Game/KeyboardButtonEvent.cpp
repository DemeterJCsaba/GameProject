#include "KeyboardButtonEvent.h"

KeyboardButtonEvent::KeyboardButtonEvent(unsigned int keyCode, unsigned int actionCode):
	Event(EVENTS::KEYBOARD_BUTTON),
	m_KeyCode(keyCode),
	m_ActionCode(actionCode)
{

}