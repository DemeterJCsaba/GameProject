#pragma once

#include "IState.h"
#include "RenderEngine2D.h"

class MainMenuState : public IState {
private:
	RenderEngine2D m_RenderEngine2D;
public:
	MainMenuState();
	void update();
	void render();
};