#pragma once

#include <math.h>

#include "IState.h"
#include "StateManager.h"
#include "Window.h"

#include "RenderEngine3DTextured.h"
#include "SkyBox.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Texture2D.h"

#include "TerrainRenderEngine.h"

#include "Entity.h"

class SinglePlayerState : public IState {
private:
	RenderEngine3DTextured m_SkyBoxRenderer;
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