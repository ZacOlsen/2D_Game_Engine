#include "Component.h"
#include "..\Misc\GameObject.h"

Component::~Component() {

	if (gameObject) {
		gameObject->removeComponent(this);
	}
}