#include <Windows.h>
#include <stdio.h>

#include "Window.h"
#include "FPSManager.h"

void main() {
	//FreeConsole();

	Window window(960, 540, "Game");
	FPSManager fps(60);
	
	double tmp1, tmp2;

	while (!window.isClosed()) {
		fps.begin();
		window.clear();
		window.update();
		fps.end();
		//window.getMousePos(&tmp1, &tmp2);
		//printf("mouse: %.0lf %.0lf\n", tmp1, tmp2);
	}

	//system("pause");
}