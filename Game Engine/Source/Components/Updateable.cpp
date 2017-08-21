#include "Updateable.h"
#include "..\Misc\GameObject.h"

Updateable::~Updateable() { 

	if (gameObject) {
		gameObject->removeComponent(this);
	}
}
