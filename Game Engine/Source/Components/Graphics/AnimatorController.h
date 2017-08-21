#pragma once

#include <time.h>
#include "..\Updateable.h"
#include "..\..\Graphics\Animation.h"
#include "Renderer.h"

class AnimatorController : public Updateable {

public:
	
	AnimatorController(const vector<Animation*> animations);
	AnimatorController(const vector<Animation*> animations, const char*& startAnimName);
	AnimatorController(const vector<Animation*> animations, const unsigned int& startAnimIndex);

	string getSaveString();
	static AnimatorController* createFromString(const string& str);

	void start();
	void update();

	void addAnimation(Animation* anim);
	void changeToAnimation(const char* name);

private:

	vector<Animation*> animations;
	unsigned int animIndex;
	unsigned int spriteIndex = 0;

	Renderer* renderer = nullptr;
	clock_t timer;
};

