#ifndef MENUGUI_H
#define MENUGUI_H

#include "GUIManager.h"
#include "TimerManeger.h"
#include "Layer2D.h"
#include "Layer3DDynamic.h"
#include "Event.h"

class MenuGui {
private:
	GUIManager<MenuGui> m_GUIManager;
	TimerManager m_TimerManager;

	Layer2D* m_LayerGuiPtr;
	Layer3DDynamic* m_Layer3DPtr;
public:
	MenuGui(Layer2D* layerGui,Layer3DDynamic* layer3D);

	void update();
	void handleEvent(Event* event);

	void start();
	void load();
private:
	int state;

	void backToMain();
	void mainButtonsIn();
	void mainButtonsOut();
	void startGameButtonExecute();
	void startGame();
	void exitGame();

	void selectCaracter();
	void selectCharacterIn();
	void selectCharacterOut();
	void createCharater();

	void fade(float value);
};

#endif // !MENUGUI_H

