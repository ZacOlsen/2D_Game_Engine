#pragma once

#include <string>
#include "..\Updateable.h"
#include "..\..\Misc\GameObject.h"
#include "..\..\Utilities\Input.h"

class Updateable;

class PlayerController : public Updateable {

public:

	string getSaveString();
	static PlayerController* createFromString(const string& str);

	void start();
	void update();
	void lateUpdate();

	void jump();
	void die();

	void onTriggerEnter(BoxCollider* col);
	void onTriggerStay(BoxCollider* col);
	void onTriggerExit(BoxCollider* col);

private:

	float speed = 5.0f;
	float jumpAccel = 1000;
	bool grounded = false;

	int lives = 3;
	Vector2 spawnPoint = Vector2(0, .75f);

	TextRenderer* text = nullptr;
	RigidBody* rb = nullptr;
	AnimatorController* animContr = nullptr;
	ParticleEmitter* emitter = nullptr;
};

