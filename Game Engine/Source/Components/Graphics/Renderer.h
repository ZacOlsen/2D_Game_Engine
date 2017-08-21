#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include "..\Component.h"
#include "..\..\Graphics\Sprite.h"

class Renderer : public Component {

public:

	static Shader shaderUI;

	Vector4 color;
	Sprite* sprite = NULL;

	Renderer(const Vector4& color = Vector4(1, 1, 1, 1), Sprite* sprite = NULL);
	~Renderer();

	std::string getSaveString();
	static Renderer* createFromString(const string& str);

	void setShader(Shader* shader);

	static void init();
	virtual void render();

protected:

	Shader* m_shader = nullptr;
	vector<Vector2> uvs;
	GLuint textureID;

	void renderSprite(const Vector2& botL, const Vector2& botR, const Vector2& topR, const Vector2& topL);
	void renderRect(const Vector2& botL, const Vector2& botR, const Vector2& topR, const Vector2& topL);
};

