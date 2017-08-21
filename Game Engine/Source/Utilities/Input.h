#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "..\Graphics\Camera.h"

using namespace std;

#define NUM_OF_KEY_SLOTS 128
#define NUM_OF_MOUSE_SLOTS 10

class Vector2;

class Input {

public:

	static void init(GLFWwindow* window);
	static void update();

	static bool getKeyPressed(int key);
	static bool getKeyDown(int key);
	static bool getKeyReleased(int key);

	static Vector2 getMousePosition();
	static bool getMouseButtonPressed(int button);
	static bool getMouseButtonDown(int button);
	static bool getMouseButtonReleased(int button);

private:
	
	static bool keysPressed[NUM_OF_KEY_SLOTS];
	static bool keysDown[NUM_OF_KEY_SLOTS];
	static bool keysReleased[NUM_OF_KEY_SLOTS];
	
	static Vector2 mousePos;
	static bool mouseButtonPressed[NUM_OF_MOUSE_SLOTS];
	static bool mouseButtonDown[NUM_OF_MOUSE_SLOTS];
	static bool mouseButtonReleased[NUM_OF_MOUSE_SLOTS];

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mousePosCallback(GLFWwindow* window, double xPos, double yPos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};