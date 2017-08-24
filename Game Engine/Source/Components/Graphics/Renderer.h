#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include "..\Component.h"
#include "..\..\Graphics\Sprite.h"

class Renderer : public Component {

public:

	Vector4 color;

	Renderer(const Vector4& color = Vector4(1, 1, 1, 1), Sprite* sprite = NULL);
	Renderer(const Vector4& color, vector<Sprite*> sprites, vector<string> locationNames);

	std::string getSaveString();
	static Renderer* createFromString(const string& str);

	void setShaderIndex(const unsigned int& index);
	static Shader* getShader(const unsigned int& index);

	void setSprites(const vector<Sprite*>& sprites);

	virtual const GLuint getTextureID(const unsigned int& index) const;

	static void init();
	virtual void render();

protected:

	static vector<Shader*> shaders;
	unsigned int shaderIndex = 0;

	vector<Sprite*> sprites;
	vector<string> locationNames;
	vector<Vector2> uvs;

	void renderSprite(const Vector2& botL, const Vector2& botR, const Vector2& topR, const Vector2& topL) const;
	void renderRect(const Vector2& botL, const Vector2& botR, const Vector2& topR, const Vector2& topL) const;
};

