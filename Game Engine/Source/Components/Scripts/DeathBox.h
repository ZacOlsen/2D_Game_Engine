#pragma once

#include "..\Updateable.h"
#include "..\..\Misc\GameObject.h"

class DeathBox : public Updateable {
	
public:

	string getSaveString();
	static DeathBox* createFromString(const string& str);

	void onTriggerEnter(BoxCollider* col);
};

