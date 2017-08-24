#pragma once

#include "..\Component.h"
#include "RectTransform.h"
#include "..\..\Misc\GameObject.h"

class Canvas : public Component {

public:
	
	bool scaleWithScreenSize = true;
	string getSaveString();
	void renderUI() const;

private:
	void renderIteration(const RectTransform* rect) const;
};

