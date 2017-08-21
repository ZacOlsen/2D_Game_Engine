#pragma once

#include <vector>
#include "Shader.h"

class Sprite {

public:

	Sprite(const char* filePath);
	~Sprite();

	static Sprite* getSprite(const char* filePath);

	void bind();
	void unbind();

	std::string getFilePath();

	GLuint textureID;
private:
	string filePath;
	static vector<Sprite*> sprites;
};

