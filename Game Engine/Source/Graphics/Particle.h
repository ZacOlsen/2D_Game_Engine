#pragma once

#include <time.h>
#include "..\Components\Graphics\SpriteRenderer.h"

class ParticleEmitter;

class Particle : public SpriteRenderer, Updateable {

public:

	Particle(ParticleEmitter* emitter, const Vector2& size = Vector2(1, 1), const Vector4& color = Vector4(1, 1, 1, 1),
		Sprite* sprite = NULL, const Vector2& pos = Vector2(), const float& lifeTime = 1);
	~Particle();

	std::string getSaveString() { return ""; }

	void update();
	void render();

private:

	float lifeTime;
	clock_t timeOfSpawn;
	Vector2 pos;
	ParticleEmitter* emitter;
};
