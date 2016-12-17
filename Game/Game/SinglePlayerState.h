#pragma once

#include <math.h>

#include "IState.h"
#include "StateManager.h"
#include "Window.h"

#include "LayerSky.h"
#include "Layer3DStatic.h"

#include "Environment.h"
#include "Planet.h"
#include "SkyBox.h"

#include "ShaderProgram.h"
#include "Camera.h"

#include "Entity.h"

class SinglePlayerState : public IState {
private:
	//LayerGUI* m_LayerGUI;
	LayerSky* m_LayerSky;

	int m_BlockCount;
	int m_BlockSize;
	float m_SpriteSize;
	Layer3DStatic*** m_Layer3DStatic;
	int m_PosX;
	int m_PosZ;

	Environment m_Environment;
	Camera* m_MainCamera;
	//std::shared_ptr<Camera> m_MainCameraPtr;
public:
	SinglePlayerState();
	~SinglePlayerState();

	void update();
	void render();

	void resume();
	void pause();
private:
	void init();

	void updateTerrain();
};