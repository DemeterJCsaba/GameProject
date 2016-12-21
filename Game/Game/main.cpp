#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#define _WINSOCKAPI_
#include "winsock2.h"

#include "SettingsManager.h"
#include "Window.h"
#include "FPSManager.h"
#include "StateManager.h"
#include "MainMenuState.h"

#pragma comment (lib, "Ws2_32.lib")

using namespace std;
void main() {
	//FreeConsole();
	
	try {
		SettingsManager settingsManager;
		settingsManager.loadSettings();

		Window::MyCreateWindow(settingsManager.getWindowSettings());
		Window* window = Window::GetInstance();
		window->addEventListener(&StateManager::getInstance());

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
		cout << "FAIL!: " << e.what() << endl;
	}
}