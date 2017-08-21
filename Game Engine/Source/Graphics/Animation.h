#pragma once

#include <vector>
#include "Sprite.h"

class Animation {

public:

	const char* name;
	float frameRate = 0;
	
	Animation(const vector<Sprite*> sprites, const float& frameRate, const char* name);
	
	string getSaveString();
	static Animation* createFromString(const string& str);

	const unsigned int spriteCount();
	Sprite*& getSprite(const unsigned int& index);

private:
	vector<Sprite*> sprites;
};

