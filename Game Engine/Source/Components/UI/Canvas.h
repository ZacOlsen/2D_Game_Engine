#pragma once

#include "..\Component.h"
#include "RectTransform.h"
#include "..\..\Misc\GameObject.h"

class Canvas : public Component {

public:
	
	string getSaveString();
	void renderUI();

private:
	void renderIteration(RectTransform* rect);
};

