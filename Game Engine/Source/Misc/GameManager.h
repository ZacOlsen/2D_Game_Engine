#pragma once

#include "GameObject.h"
#include "..\Graphics\Camera.h"
#include "..\Utilities\Scene.h"
#include "..\Components\Scripts\PlayerController.h"
#include "..\Components\Scripts\DeathBox.h"

class Canvas;

class GameManager {

public:
	
	static void init();
	static void addGameObject(GameObject* go);
	static void removeGameObject(GameObject* go);
	static GameObject* findGameObject(const char* tag);

	static void onStart();
	static void onFrame();

	static Transform* getTransformOfID(const unsigned short& id);

private:

	static float physLagTime;
	static clock_t prevFrame;

	static vector<GameObject*> gameObjects;
	static Canvas* canvas;

	static void maunalWorldBuild();
	static void buildPiramid(const float& startx, const float& starty, const float& direction = 1);
};

