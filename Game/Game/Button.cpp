#include "Button.h"

Button::Button(vec2 position, vec2 size, Texture* texture, void(*function)()):
	GUIImage(position,size,texture),
	m_Function(function)
{

}

void Button::execute() {
	m_Function();
}