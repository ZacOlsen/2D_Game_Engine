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
	unsigned int width;
	unsigned int height;

	GLFWwindow* window;

	bool init();

public:
	Window(const char* title, const unsigned int& width, const unsigned int& height);
	~Window();

	GLFWwindow* getWindow();

	void clear() const;
	void update();
	bool closed() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
};

