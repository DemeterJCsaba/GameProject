#include "SettingsManager.h"
#include "Window.h"
#include "FPSManager.h"
#include "StateManager.h"
#include "MainMenuState.h"

using namespace std;
void main() {
	//FreeConsole();
	
	SettingsManager settingsManager;
	settingsManager.loadSettings();

	Window::CreateWindow(settingsManager.getWindowSettings());
	Window* window = Window::GetInstance();

	StateManager::getInstance().addState(new MainMenuState());

	while (!window->isClosed()) {
		FPSManager::getInstance().begin();

		window->clear();
		window->update();

		StateManager::getInstance().Update();
		
		StateManager::getInstance().getCurrentState()->update();
		StateManager::getInstance().getCurrentState()->render();

		window->render();

		FPSManager::getInstance().end();
	}

	StateManager::getInstance().closeAll();
	Texture::clearTextures();
	Window::CloseWindow();

	settingsManager.saveSettings();
}