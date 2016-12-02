#include "Window.h"
#include "FPSManager.h"
#include "StateManager.h"
#include "MainMenuState.h"

using namespace std;
void main() {
	//FreeConsole();

	SettingsManager::LoadSettings();
	Window::getInstance();
	StateManager::getInstance().addState(new MainMenuState());

	while (!Window::getInstance().IsClosed()) {
		FPSManager::getInstance().begin();

		Window::getInstance().Clear();
		Window::getInstance().Update();

		StateManager::getInstance().getCurrentState()->update();
		StateManager::getInstance().getCurrentState()->render();

		Window::getInstance().Render();

		StateManager::getInstance().Update();
		FPSManager::getInstance().end();
	}

	StateManager::getInstance().closeAll();

	SettingsManager::SaveSettings();
}