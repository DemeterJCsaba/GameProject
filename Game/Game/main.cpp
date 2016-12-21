#include "SettingsManager.h"
#include "Window.h"
#include "FPSManager.h"
#include "StateManager.h"
#include "MainMenuState.h"

using namespace std;
void main() {
	//FreeConsole();
	
	try {
		SettingsManager settingsManager;
		settingsManager.loadSettings();

		Window::CreateWindow(settingsManager.getWindowSettings());
		Window* window = Window::GetInstance();
		window->subscribe(&StateManager::getInstance());

		StateManager::getInstance().addState(new MainMenuState());

		while (!window->isClosed()) {
			FPSManager::getInstance().begin();

			window->clear();
			window->update();

			StateManager::getInstance().update();

			StateManager::getInstance().getCurrentState()->update();
			StateManager::getInstance().getCurrentState()->render();

			window->render();

			FPSManager::getInstance().end();
		}

		Texture::clearTextures();
		Window::CloseWindow();

		settingsManager.saveSettings();
	}
	catch (exception& e) {
		cout << "Game loop exception!: " << e.what() << endl;
	}
}