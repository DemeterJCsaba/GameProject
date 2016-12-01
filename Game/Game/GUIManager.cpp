#include "GUIManager.h"

void GUIManager::addButton(Button* button) {
	m_Buttons.push_back(button);
}

void GUIManager::execute() {
	if (Window::getInstance().getMousePressed(GLFW_MOUSE_BUTTON_1)) {
		double x = (Window::getInstance().getMousePosX() / Window::getInstance().getWidth())*2.0 - 1.0;
		double y = (1.0 - Window::getInstance().getMousePosY() / Window::getInstance().getHeight())*2.0 - 1.0;

		for (Button* button : m_Buttons) {
			if (x >= (button->getPosition().x) &&
				x <= (button->getPosition().x + button->getSize().x) &&
				y >= (button->getPosition().y) &&
				y <= (button->getPosition().y + button->getSize().y)) {
				button->execute();
			}
		}
	}
}