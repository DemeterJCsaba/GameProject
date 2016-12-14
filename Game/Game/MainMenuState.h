#pragma once

#include "IState.h"
#include "RenderEngine2D.h"
#include "ShaderProgram.h"
#include "Window.h"
#include "StateManager.h"
#include "SinglePlayerState.h"
#include "GUIManager.h"
#include "LayerGUI.h"
#include "Layer3DDynamic.h"

//class LayerGUI;
//class Layer3DDynamic;
//class GUIManager;

class MainMenuState : public IState {
private:
	LayerGUI* m_LayerGUI; // csoreh!!!
	//std::shared_ptr<Layer3DDynamic> m_LayerGuiPtr;
	Layer3DDynamic* m_Layer3D;

	GUIManager m_GUIManager;
public:
	MainMenuState();
	~MainMenuState();

	void update();
	void render();

	void resume();
	void pause();
private:
	void init();
};