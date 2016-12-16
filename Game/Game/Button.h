#pragma once

#include "GUIImage.h"

template <class T>
class Button : public GUIImage {
private:
	void (T::*m_Function)();
	T* m_Object;

public:
	Button(vec2 position, vec2 size, Texture* texture, void (T::*function)(),T* object) :
		GUIImage(position, size, texture),
		m_Function(function),
		m_Object(object)
	{

	}

	void execute() {
		(m_Object->*m_Function)();
	}
};