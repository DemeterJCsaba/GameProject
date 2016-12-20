#include "MouseButtonEvent.h"

MouseButtonEvent::MouseButtonEvent(unsigned int keyCode, unsigned int actionCode):
	Event(EVENTS::MOUSE_BUTTON),
	m_KeyCode(keyCode),
	m_ActionCode(actionCode)
{

}