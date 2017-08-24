#pragma once

#include <GL\glew.h>
#include <string>
#include "..\Math\Matrix3.h"

class GameObject;

class Component {

public:
	GameObject* gameObject = nullptr;

	virtual ~Component();

	virtual std::string getSaveString() = 0;
};

