#ifndef BUTTON_H
#define BUTTON_H

#include "GUIImage.h"
#include "Text.h"

template <class T>
class Button : public GUIImage {
private:
	string m_Text;
	void (T::*m_Function)();
	T* m_Object;

public:
	Button(string text,vec2 position, vec2 size, void (T::*function)(),T* object) :
		m_Text(text),
		GUIImage(position, size, Texture2D::get("Button.png")),
		m_Function(function),
		m_Object(object)
	{
		m_Models.push_back(new Text(m_Text, vec2(0.02f, size.y - 0.02f), 0.5f));
	}

	void execute() {
		(m_Object->*m_Function)();
	}
};

#endif // !BUTTON_H