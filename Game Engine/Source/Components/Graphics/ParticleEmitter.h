#pragma once

#include <vector>
#include <time.h>
#include "..\Updateable.h"
#include "..\Transform.h"
#include "..\..\Graphics\Sprite.h"

class Particle;

class ParticleEmitter : public Updateable {

public:

	bool enabled = true;

	Vector2 rateRange;
	Vector2 lifeTimeRange;
	Vector2 localCenterOffset;
	Vector2 spawnRange;
	Vector2 sizeRange;

	Sprite* sprite;

	ParticleEmitter(const Vector2& rateRange, const Vector2& lifeTimeRange, const Vector2& localCenterOffset, 
		const Vector2& spawnRange, const Vector2& sizeRange);

	string getSaveString() { return ""; }

	void start();
	void update();
	void addColor(const Vector4& color);
	void remove(Particle* p);

private:
	
	clock_t timeOfPrevSpawn = 0;
	float timeTilNextSpawn = 0;

	vector<Vector4> colors;
	vector<Particle*> particles;

	Transform* transform;
};

