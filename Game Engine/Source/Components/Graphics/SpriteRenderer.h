#pragma once

#include "Renderer.h"
#include "..\..\Misc\GameObject.h"

class SpriteRenderer : public Renderer {

public:

	Vector2 size;

	SpriteRenderer(const Vector2& size = Vector2(1, 1), const Vector4& color = Vector4(1, 1, 1, 1), Sprite* sprite = NULL);
	SpriteRenderer(const Vector2& size, const Vector4& color, vector<Sprite*> sprites, vector<string> locationNames);
	~SpriteRenderer();
	
	string getSaveString();
	static SpriteRenderer* createFromString(const string& string);

	static void init();
	static void renderAllSprites();

	void render();

protected:

	static vector<SpriteRenderer*> spriteRenders;

	void renderSprite(const Vector2& botL, const Vector2& botR, const Vector2& topR, const Vector2& topL,
		const Vector2& worldBotL, const Vector2& worldBotR, const Vector2& worldTopR, const Vector2& worldTopL);
};

