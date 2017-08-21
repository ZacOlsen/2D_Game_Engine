#include "Camera.h"

float Camera::size = 8;
Transform* Camera::transform;
unsigned int Camera::m_Width;
unsigned int Camera::m_Height;
Matrix3 Camera::cameraMatrix;

void Camera::init(Transform* trans, GLFWwindow* window) {
	
	Camera::transform = trans;
	glfwSetFramebufferSizeCallback(window, windowResizeCallBack);
//	transform->setLocaLRotation(45);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	windowResizeCallBack(window, width, height);
}

void Camera::calculateCameraMatrix() {
	cameraMatrix = transform->getTransformation().invert();
}

const Matrix3& Camera::getCameraMatrix() {
	return cameraMatrix;
}

const unsigned int& Camera::getWidth() {
	return m_Width;
}

const unsigned int& Camera::getHeight() {
	return m_Height;
}

void Camera::windowResizeCallBack(GLFWwindow* window, int width, int height) {

	m_Width = width;
	m_Height = height;

	glViewport(0, 0, width, height);

	if (width > height) {
		transform->setLocaLScale(1.0f / size, ((float)height / (float)width) / size);
	} else if (height > width) {
		transform->setLocaLScale(((float)width) / ((float)height) / size, 1.0f / size);
	} else {
		transform->setLocaLScale(1.0f / size, 1.0f / size);
	}
}
