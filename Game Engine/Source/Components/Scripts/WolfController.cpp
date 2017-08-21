#include "WolfController.h"

void WolfController::start() {
	rb = gameObject->getComponent<RigidBody>();
	rb->velocity.x = speed;
}

void WolfController::update() {

	if (shouldDie) {
		pc->die();
		shouldDie = false;
	}

	rb->velocity.x = gameObject->transform->getLocalScale().x * speed;
}

void WolfController::onCollisionEnter(BoxCollider* col) {

	if (col->gameObject->tag == "Tower") {
		gameObject->transform->setLocaLScale(-gameObject->transform->getLocalScale().x, 1);

	} else if (col->gameObject->tag == "Player") {
		pc = col->gameObject->getComponent<PlayerController>();
		shouldDie = true;
	}
}

void WolfController::onTriggerEnter(BoxCollider* col) {

	if (col->gameObject->tag == "Ground Check") {
		gameObject->destroy();
		col->gameObject->getComponent<PlayerController>()->jump();
	}
}
