#pragma once

#include "Component.h"

class BoxCollider;

class Updateable : public Component {

public:

	virtual void start() {};
	virtual void update() {};
	virtual void lateUpdate() {};

	virtual void onCollisionEnter(BoxCollider* col) {};
	virtual void onCollisionStay(BoxCollider* col) {};
	virtual void onCollisionExit(BoxCollider* col) {};
				 
	virtual void onTriggerEnter(BoxCollider* col) {};
	virtual void onTriggerStay(BoxCollider* col) {};
	virtual void onTriggerExit(BoxCollider* col) {};
};