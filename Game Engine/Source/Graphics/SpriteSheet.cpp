#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const char* fileName, const unsigned int& spriteWidths, const unsigned int& spriteHeights)
	: Sprite(fileName), spriteWidths(spriteWidths), spriteHeights(spriteHeights), rowNums(height / spriteHeights),
	colNums(width / spriteWidths) {

	if (width % spriteWidths != 0 || height % spriteHeights != 0) {
		throw exception();
	}
}

const vector<Vector2> SpriteSheet::getSpriteUVs(const unsigned int& spriteNum) const {

	if (spriteNum >= colNums * rowNums) {
		throw exception();
	}

	const unsigned int col = spriteNum % colNums;
	const unsigned int row = spriteNum / colNums;

	return getSpriteUVs(col, row);
}

const vector<Vector2> SpriteSheet::getSpriteUVs(const unsigned int& col, const unsigned int& row) const {

	vector<Vector2> uvs;

	uvs.push_back(Vector2(col * spriteWidths, (row + 1) * spriteHeights));
	uvs.push_back(Vector2((col + 1) * spriteWidths, (row + 1) * spriteHeights));
	uvs.push_back(Vector2((col + 1) * spriteWidths, row * spriteHeights));
	uvs.push_back(Vector2(col * spriteWidths, row * spriteHeights));

	for (unsigned int i = 0; i < uvs.size(); i++) {
		uvs[i].x /= (float)width;
		uvs[i].y /= (float)height;
	}

	return uvs;
}

