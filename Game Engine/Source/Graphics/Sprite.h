#pragma once

#include <vector>
#include "Shader.h"

class Sprite {

public:

	Sprite(const char* filePath);

	static Sprite* getSprite(const char* filePath);

	const GLuint getTextureID();
	std::string getFilePath();

	void bind();
	void unbind();

private:

	static vector<Sprite*> sprites;
	
	GLuint textureID;
	const string filePath;
};

