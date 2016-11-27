#pragma once

#include "IState.h"
#include "RenderEngine2D.h"
#include "ShaderProgram.h"
#include "Window.h"
#include "StateManager.h"
#include "SinglePlayerState.h"
#include "RenderEngine3DDynamic.h"

class MainMenuState : public IState {
private:
	RenderEngine2D m_RenderEngine2D;
	ShaderProgram m_ShaderGUI;

	RenderEngine3DDynamic m_RenderEngine3DDynamic;
	ShaderProgram m_Shader3D;

	Entity* player;
public:
	MainMenuState();
	~MainMenuState();

	void update();
	void render();
};