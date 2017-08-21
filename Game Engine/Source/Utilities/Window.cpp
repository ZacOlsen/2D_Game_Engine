#include "Window.h"

Window::Window(const char* title, const unsigned int& width, const unsigned int& height) {

	this->title = title;
	this->width = width;
	this->height = height;

	if (!init()) {
		glfwTerminate();
	}

	glfwSwapInterval(1);
	Input::init(window);
	Camera::init(new Transform(), window);
}

Window::~Window() {
	glfwTerminate();
}

GLFWwindow* Window::getWindow() {
	return window;
}

bool Window::init() {

	if (!glfwInit()) {
		cout << "glfw failed to init" << endl;
		return false;
	}

	if (!glewInit()) {
		cout << "glew failed to init" << endl;
		return false;
	}

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (!window) {
		cout << "failed to create" << endl;
		return false;
	}

	glfwMakeContextCurrent(window);
	return true;
}

void Window::clear() const {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update() {

	glfwPollEvents();
	glfwSwapBuffers(window);
}

bool Window::closed() const {
	return glfwWindowShouldClose(window) == 1;
}

