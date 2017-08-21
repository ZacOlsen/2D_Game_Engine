#include "Input.h"

bool Input::keysPressed[];
bool Input::keysDown[];
bool Input::keysReleased[];
Vector2 Input::mousePos;
bool Input::mouseButtonPressed[];
bool Input::mouseButtonDown[];
bool Input::mouseButtonReleased[];

void Input::init(GLFWwindow* window) {

	glfwSetKeyCallback(window, Input::keyCallback);
	glfwSetCursorPosCallback(window, Input::mousePosCallback);
	glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
}

void Input::update() {

	for (unsigned int i = 0; i < NUM_OF_KEY_SLOTS; i++) {
		keysPressed[i] = false;
		keysReleased[i] = false;

		if (i < NUM_OF_MOUSE_SLOTS) {
			mouseButtonPressed[i] = false;
			mouseButtonReleased[i] = false;
		}
	}
}

bool Input::getKeyPressed(int key) {
	return keysPressed[key];
}

bool Input::getKeyDown(int key) {
	return keysDown[key];
}

bool Input::getKeyReleased(int key) {
	return keysReleased[key];
}

Vector2 Input::getMousePosition() {
	return mousePos;
}

bool Input::getMouseButtonPressed(int button) {
	return mouseButtonPressed[button];
}

bool Input::getMouseButtonDown(int button) {
	return mouseButtonDown[button];
}
bool Input::getMouseButtonReleased(int button) {
	return mouseButtonReleased[button];
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key >= NUM_OF_KEY_SLOTS) {
		return;
	}

	if (action == GLFW_PRESS) {
		keysDown[key] = true;
		keysPressed[key] = true;
	}

	if (action == GLFW_RELEASE) {
		keysDown[key] = false;
		keysReleased[key] = true;
	}
}

void Input::mousePosCallback(GLFWwindow* window, double xPos, double yPos) {
	
	mousePos.x = (float)xPos - Camera::getWidth() / 2.0f;
	mousePos.y = -1 * ((float)yPos - Camera::getHeight() / 2.0f);
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

	if (button >= NUM_OF_MOUSE_SLOTS) {
		return;
	}

	if (action == GLFW_PRESS) {
		mouseButtonPressed[button] = true;
		mouseButtonDown[button] = true;
	}

	if (action == GLFW_RELEASE) {
		mouseButtonDown[button] = false;
		mouseButtonReleased[button] = true;
	}
}