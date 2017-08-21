#pragma once

#include "..\Misc\GameManager.h"

class Scene {

public:

	Scene(const char* name);
	~Scene();

	void saveScene(const vector<GameObject*>& gameObjects);
	void loadScene();

private:

	const char* name;
};

