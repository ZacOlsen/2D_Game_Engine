#pragma once

#include "..\Updateable.h"
#include "..\..\Misc\GameObject.h"

class PlayerController;

class WolfController : public Updateable {

public:

	string getSaveString() { return ""; }

	void start();
	void update();

	void onCollisionEnter(BoxCollider* col);
	void onTriggerEnter(BoxCollider* col);

private:

	float speed = 5;
	RigidBody* rb;

	bool shouldDie = false;
	PlayerController* pc;
};

