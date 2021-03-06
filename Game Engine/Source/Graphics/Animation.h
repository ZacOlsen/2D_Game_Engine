#pragma once

#include <vector>
#include "Sprite.h"

class Animation {

public:

	const char* name;
	float frameRate = 0;
	
	Animation(const vector<vector<Sprite*>> sprites, const float& frameRate, const char* name);
	
	string getSaveString();
	static Animation* createFromString(const string& str);

	const unsigned int spriteCount() const;
	const vector<Sprite*> getSpriteSet(const unsigned int& index) const;

private:
	vector<vector<Sprite*>> sprites;
};

