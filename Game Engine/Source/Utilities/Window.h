#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Input.h"
#include "..\Graphics\Camera.h"

using namespace std;

class Window {

private:

	const char* title;
	GLFWwindow* window;

public:
	Window(const char* title, const unsigned int& width, const unsigned int& height);
	~Window();

	GLFWwindow* getWindow();

	void clear() const;
	void update();
	bool closed() const;
};

