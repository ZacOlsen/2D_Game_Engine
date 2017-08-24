#define GLEW_STATIC

#include <iostream>
#include <time.h>
#include "Utilities\Window.h"
#include "Misc\GameManager.h"

int main() {

	Window window("game", 960, 540);
	glClearColor(0, 0, 0, 1);

	glewInit();

	cout << glGetString(GL_VERSION) << endl;

	srand(time(0));

	GameManager::init();

	clock_t t, prev;
	t = clock();
	prev = clock();
	int counter = 0;

	while (!window.closed()) {

		window.clear();
		GameManager::onFrame();

		counter++;
		if ((float)(clock() - t) / CLOCKS_PER_SEC >= 1.0f) {
			cout << counter << endl;
			counter = 0;
			t = clock();
		}

		window.update();
	}

//	system("PAUSE");
}