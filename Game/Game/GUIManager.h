#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <vector>

#include "Button.h"
#include "Window.h"
#include "MouseButtonEvent.h"
#include "Slider.h"

using namespace std;

template <class T>
class GUIManager {
private:
	vector<Button<T>*> m_Buttons;
	vector<Slider*> m_Sliders;
public:

	void addButton(Button<T>* button) {
		m_Buttons.push_back(button);
	}

	void execute(MouseButtonEvent* event) {
		if(event->getKeyCode() == GLFW_MOUSE_BUTTON_1){
			if (event->getActionCode() == GLFW_PRESS) {
				double x = (Window::GetInstance()->getMousePosX() / Window::GetInstance()->getWidth())*2.0 - 1.0;
				double y = (1.0 - Window::GetInstance()->getMousePosY() / Window::GetInstance()->getHeight())*2.0 - 1.0;

				for (auto button : m_Buttons) {
					if (x >= (button->getPosition().x) &&
						x <= (button->getPosition().x + button->getSize().x) &&
						y >= (button->getPosition().y) &&
						y <= (button->getPosition().y + button->getSize().y)) {
						button->execute();
					}
				}

				for (auto slider : m_Sliders) {
					if (x >= (slider->getPosition().x) &&
						x <= (slider->getPosition().x + slider->getSize().x) &&
						y >= (slider->getPosition().y) &&
						y <= (slider->getPosition().y + slider->getSize().y)) {
						slider->setFocus(true);
					}
				}
			}
			else {
				for (auto slider : m_Sliders) {
					slider->setFocus(false);
				}
			}
		}
	}

	void addSlider(Slider* slider) {
		m_Sliders.push_back(slider);
	}

	void update() {
		for (auto slider : m_Sliders) {
			if (slider->getFocus()) {
				float x = ((float)Window::GetInstance()->getMousePosX() / Window::GetInstance()->getWidth())*2.0f - 1.0f;
				slider->setSliderPosition(x);
			}
		}
	}
};

#endif // !GUIMANAGER_H