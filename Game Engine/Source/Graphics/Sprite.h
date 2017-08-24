#pragma once

#include <vector>
#include "Shader.h"

class Sprite {

public:

	Sprite(const char* fileName);

	static Sprite* getSprite(const char* fileName);

	const GLuint getTextureID() const;
	const std::string getFileName() const;

	const unsigned int& getWidth() const;
	const unsigned int& getHeight() const;

	void bind() const;
	void unbind() const;

protected:

	static vector<Sprite*> sprites;
	
	unsigned int width;
	unsigned int height;

	GLuint textureID;
	const string fileName;
};

