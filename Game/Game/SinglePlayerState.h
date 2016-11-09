#pragma once

#include "IState.h"
#include "StateManager.h"
#include "Window.h"

#include "SkyBoxRenderEngine.h"
#include "ShaderProgram.h"

class SinglePlayerState : public IState {
private:
	SkyBoxRenderEngine m_SkyRender;
	SkyBox m_SkyBox;
	ShaderProgram m_SkyShader;

	float tmp1 = 0;
	float tmp2 = 0;
public:
	SinglePlayerState();
	~SinglePlayerState();
	void update();
	void render();
};