#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

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
#include "TimerManeger.h"

using namespace std;

class MainMenuState : public IState {
private:
	shared_ptr<LayerGUI> m_LayerGuiBGPtr;
	shared_ptr<LayerGUI> m_LayerGuiPtr;
	shared_ptr<Layer3DDynamic> m_Layer3DPtr;

	GUIManager<MainMenuState> m_GUIManager;
	TimerManager m_TimerManager;
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

	void backToMain();
	void mainButtonsIn();
	void mainButtonsOut();
	void startGameButtonExecute();
	void startGame();
	void exitGame();
	void selectCaracter();
	void fade(float value);
};

#endif // !MAINMENUSTATE_H