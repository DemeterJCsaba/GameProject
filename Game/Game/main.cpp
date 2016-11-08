#include "Debug.h"
#include "Window.h"
#include "FPSManager.h"
#include "StateManager.h"
#include "MainMenuState.h"

using namespace std;
void main() {
#if !DEBUG_MODE
	FreeConsole();
#endif
	SettingsManager::LoadSettings();
	Window::getInstance();
	FPSManager fps(60);

	StateManager::getInstance().pushState(new MainMenuState());

	while (!Window::getInstance().isClosed()) {
		fps.begin();
		Window::getInstance().clear();

		StateManager::getInstance().getCurrentState()->update();
		StateManager::getInstance().getCurrentState()->render();

		Window::getInstance().update();
		fps.end();
	}

	SettingsManager::SaveSettings();
}