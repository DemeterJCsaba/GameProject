#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <memory>

#include "IState.h"
#include "Layer2D.h"
#include "Layer3DDynamic.h"
#include "MenuGui.h"

using namespace std;

class MainMenuState : public IState {
private:
	Layer2D m_LayerBG;
	Layer2D m_LayerGui;
	Layer3DDynamic m_Layer3DDynamic;

	MenuGui m_Gui;
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

#endif // !MAINMENUSTATE_H