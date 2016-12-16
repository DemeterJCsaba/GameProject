#pragma once

#include <memory>

#include "IState.h"
#include "RenderEngine2D.h"
#include "ShaderProgram.h"
#include "Window.h"
#include "StateManager.h"
#include "SinglePlayerState.h"
#include "GUIManager.h"
#include "LayerGUI.h"
#include "Layer3DDynamic.h"
#include "InterpolationManeger.h"

using namespace std;

class MainMenuState : public IState {
private:
	shared_ptr<LayerGUI> m_LayerGuiPtr;
	shared_ptr<Layer3DDynamic> m_Layer3DPtr;

	GUIManager m_GUIManager;
	InterpolationManager m_InterpolationManager;
	Camera m_Camera;
public:
	MainMenuState();
	~MainMenuState();

	void update();
	void render();

	void resume();
	void pause();
private:
	void init();
	void load();
};