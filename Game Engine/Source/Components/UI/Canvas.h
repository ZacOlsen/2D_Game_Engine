#pragma once

#include "..\Component.h"
#include "RectTransform.h"
#include "..\..\Misc\GameObject.h"

class Canvas : public Component {

public:
	
	bool scaleWithScreenSize = true;
	string getSaveString();
	void renderUI();

private:
	void renderIteration(RectTransform* rect);
};

