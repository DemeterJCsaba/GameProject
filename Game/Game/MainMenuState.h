#pragma once

#include "IState.h"

class MainMenuState : public IState {
private:

public:
	MainMenuState();
	void update();
	void render();
};