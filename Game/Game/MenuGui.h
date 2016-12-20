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
	enum STATES {MAIN,SELECT_CHARACTER,CREATE_CHARACTER};
	int state;

	// Main state 
	void stateMainIn();
	void stateMainOut();
	void startGame();
	void startGameButtonExecute();
	void exitGame();
	void selectCaracter();
	void fade(float value);

	// Select character state
	void stateSelectCharacterIn();
	void stateSelectCharacterOut();
	void back();
	void newCharater();
	void next();
	void previous();

	// Create character
	void stateCreateCharacterIn();
	void stateCreateCharacterOut();
	void createCharacter();
};

#endif // !MENUGUI_H

