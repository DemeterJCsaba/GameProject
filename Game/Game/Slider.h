#ifndef SLIDER_H
#define SLIDER_H

#include "GUIImage.h"
#include "Text.h"

//template <class T,class V>
class Slider : public GUIImage {
private:
	float m_Start;
	float m_End;
	float m_Value;

	bool m_Focused;
public:
	Slider(vec2 position, vec2 size,float start,float end):
		GUIImage(position, size, Texture2D::get("Slider.png")),
		m_Start(start),
		m_End(end)
	{
		m_Models.push_back(new GUIImage(vec2(0.0f,0.0f),vec2(0.02f,size.y), Texture2D::get("SliderDot.png")));
		m_Focused = false;
		m_Value = m_Start;
	}

	void setSliderPosition(float xpos) {
		float x = xpos - m_Position.x;
		x = x < 0 ? 0 : x;
		x = x / m_Size.x;
		x = x > 1.0f ? 1.0f : x;
		m_Value = m_Start + (m_End - m_Start)*x;
		m_Models.front()->setPosition(vec2((m_Size.x-0.02f)*x,0.0f));
	}
	
	void setValue(float value) {
		float tmp = value < m_Start ? m_Start : value;
		m_Value = tmp > m_End ? m_End : tmp;
		m_Models.front()->setPosition(vec2((m_Size.x - 0.02f)*((m_Value-m_Start)/(m_End-m_Start)), 0.0f));
	}

	void setFocus(bool value) { m_Focused = value; }
	bool getFocus() const { return m_Focused; }

	float getValue() const { return m_Value; }
};

#endif // !SLIDER_H
