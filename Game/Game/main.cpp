#include <stdio.h>

#include "Window.h"

void main() {
	Window window(800, 600, "Game");
	
	double tmp1, tmp2;

	while (!window.isClosed()) {
		window.clear();
		window.update();
		window.getMousePos(&tmp1, &tmp2);
		printf("mouse: %lf %lf\n", tmp1, tmp2);
	}

	system("pause");
}