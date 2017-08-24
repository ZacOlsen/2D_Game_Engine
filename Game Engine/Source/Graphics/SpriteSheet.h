#pragma once

#include "Sprite.h"

class SpriteSheet :	public Sprite {

public:

	const unsigned int spriteWidths;
	const unsigned int spriteHeights;
	const unsigned int rowNums;
	const unsigned int colNums;

	SpriteSheet(const char* fileName, const unsigned int& spriteWidths, const unsigned int& spriteHeights);

	const vector<Vector2> getSpriteUVs(const unsigned int& spriteNum) const; //counts across then down
	const vector<Vector2> getSpriteUVs(const unsigned int& col, const unsigned int& row) const;
};

