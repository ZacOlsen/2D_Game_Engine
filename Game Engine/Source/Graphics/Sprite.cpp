#include "Sprite.h"

vector<Sprite*> Sprite::sprites;

Sprite::Sprite(const char* filePath) : filePath(filePath) {

	string file = "..\\Game Engine\\Assets\\Images\\" + this->filePath;

	unsigned int width, height;
	BYTE* bits = Utilities::loadImage(file.c_str(), &width, &height);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);

	sprites.push_back(this);
}

Sprite* Sprite::getSprite(const char* filePath) {
	
	for (unsigned int i = 0; i < sprites.size(); i++) {
		if (!strcmp(sprites[i]->filePath.c_str(), filePath)) {
			return sprites[i];
		}
	}

	return new Sprite(filePath);
}

const GLuint Sprite::getTextureID() {
	return textureID;
}

void Sprite::bind() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Sprite::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::string Sprite::getFilePath() {
	return filePath;
}