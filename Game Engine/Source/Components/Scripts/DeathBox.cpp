#include "DeathBox.h"

string DeathBox::getSaveString() {
	
	string save = "DeathBox\n";
	return save;
}

DeathBox* DeathBox::createFromString(const string& str) {
	return new DeathBox();
}

void DeathBox::onTriggerEnter(BoxCollider* col) {

	if (col->gameObject->tag == "Player") {
		GameObject* go = col->gameObject;
		PlayerController* pc = go->getComponent<PlayerController>();
		pc->die();
	}
}