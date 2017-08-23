#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\Components\Transform.h"
//#include "..\Misc\GameManager.h"

class Camera {

public:

	static float size;
	static Transform* transform;
	
	static void init(Transform* trans, GLFWwindow* window);
	static void calculateCameraMatrix();
	static const Matrix3& getCameraMatrix();
	const static unsigned int& getWidth();
	const static unsigned int& getHeight();

private:

	static unsigned int m_Width;
	static unsigned int m_Height;

	static Matrix3 cameraMatrix;

	static void windowResizeCallBack(GLFWwindow* window, int width, int height);
};

