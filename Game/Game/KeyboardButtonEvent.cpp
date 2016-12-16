#include "KeyboardButtonEvent.h"

KeyboardButtonEvent::KeyboardButtonEvent(unsigned int buttonCode):
	Event("KeyboardButtonEvent"),
	m_ButtonCode(buttonCode)
{

}