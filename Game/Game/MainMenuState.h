#pragma once

#include "IState.h"
#include "RenderEngine2D.h"
#include "ShaderProgram.h"

class MainMenuState : public IState {
private:
	RenderEngine2D m_RenderEngine2D;
	ShaderProgram m_Shader;
public:
	MainMenuState();
	~MainMenuState();
	void update();
	void render();
};