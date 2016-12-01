#pragma once

#include <vector>

#include "Button.h"
#include "Window.h"

using namespace std;

class GUIManager {
private:
	vector<Button*> m_Buttons;
public:

	void addButton(Button* button);
	void execute();
};