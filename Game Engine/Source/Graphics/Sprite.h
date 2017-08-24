#pragma once

#include <vector>
#include "Shader.h"

class Sprite {

public:

	Sprite(const char* fileName);

	static Sprite* getSprite(const char* fileName);

	const GLuint getTextureID();
	std::string getFilePath();

	const unsigned int& getWidth() const;
	const unsigned int& getHeight() const;

	void bind();
	void unbind();

protected:

	static vector<Sprite*> sprites;
	
	unsigned int width;
	unsigned int height;

	GLuint textureID;
	const string fileName;
};

