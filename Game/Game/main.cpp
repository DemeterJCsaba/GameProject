#include <stdio.h>

#include "Debug.h"
#include "Window.h"
#include "FPSManager.h"
#include <string>
#include "StateManager.h"

using namespace std;
void main() {
	//FreeConsole();

	Window window(960, 540, "Game");
	FPSManager fps(60);
	
	double tmp1, tmp2;

	while (!window.isClosed()) {
		fps.begin();
		window.clear();
		window.update();
		if (window.keyPressed(GLFW_KEY_E))
			break;
		fps.end();
		window.getMousePos(&tmp1, &tmp2);
		//printf("mouse: %.0lf %.0lf\n", tmp1, tmp2);
		//DEBUG("" + to_string(tmp1));
		StateManager::getInstance();
	}

	//system("pause");
}