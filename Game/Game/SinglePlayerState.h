#pragma once

#include <math.h>

#include "IState.h"
#include "StateManager.h"
#include "Window.h"

#include "SkyBoxRenderEngine.h"
#include "ShaderProgram.h"
#include "Camera.h"

#include "TerrainRenderEngine.h"

#include"Entity.h"

class SinglePlayerState : public IState {
private:
	SkyBoxRenderEngine m_SkyRender;
	SkyBox m_SkyBox;
	ShaderProgram m_SkyShader;

	Camera m_Camera;

	double m_Time;
	vec3 m_SunPosition;

	double tmpx, tmpy;

	TerrainRenderEngine m_TerrainRenderer;
	Terrain m_Terrain;
	ShaderProgram m_Shader;
public:
	SinglePlayerState();
	~SinglePlayerState();
	void update();
	void render();
};