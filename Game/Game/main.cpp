#include "Window.h"
#include "FPSManager.h"
#include "StateManager.h"
#include "MainMenuState.h"

using namespace std;
void main() {
	//FreeConsole();
	SettingsManager::LoadSettings();
	Window::getInstance();
	FPSManager fps(60);

	StateManager::getInstance().addState(new MainMenuState());

	while (!Window::getInstance().IsClosed()) {
		fps.begin();
		Window::getInstance().Clear();
		Window::getInstance().Update();

		StateManager::getInstance().getCurrentState()->update();
		StateManager::getInstance().getCurrentState()->render();

		Window::getInstance().Render();
		fps.end();
	}

	while (StateManager::getInstance().closeCurrentState());

	SettingsManager::SaveSettings();
}