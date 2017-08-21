#pragma once

#include <GL\glew.h>
#include <string>
#include "..\Math\Matrix3.h"

class GameObject;

class Component {

public:
	GameObject* gameObject = nullptr;

	Component();
	virtual ~Component() {};

	virtual std::string getSaveString() = 0;
};

