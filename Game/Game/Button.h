#pragma once

#include "GUIImage.h"

class Button : public GUIImage {
private:
	void (*m_Function)();
public:
	Button(vec2 position, vec2 size, Texture* texture,void (*function)());
	void execute();
};