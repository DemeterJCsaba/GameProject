#include <stdio.h>

#include "Debug.h"
#include "Window.h"
#include "FPSManager.h"
#include <string>
#include "StateManager.h"
#include "MainMenuState.h"

using namespace std;
void main() {
#if !DEBUG_MODE
	FreeConsole();
#endif

	Window window(960, 540, "Game");
	FPSManager fps(60);

	StateManager::getInstance().pushState(new MainMenuState());

	while (!window.isClosed()) {
		fps.begin();
		window.clear();

		StateManager::getInstance().getCurrentState()->update();
		StateManager::getInstance().getCurrentState()->render();

		window.update();
		fps.end();
	}
}