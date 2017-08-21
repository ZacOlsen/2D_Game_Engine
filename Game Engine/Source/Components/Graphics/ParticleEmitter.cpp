#include "ParticleEmitter.h"
#include "..\..\Graphics\Particle.h"

ParticleEmitter::ParticleEmitter(const Vector2& rateRange, const Vector2& lifeTimeRange, const Vector2& localCenterOffset,
	const Vector2& spawnRange, const Vector2& sizeRange) {

	this->rateRange = rateRange;
	this->lifeTimeRange = lifeTimeRange;
	this->localCenterOffset = localCenterOffset;
	this->spawnRange = spawnRange;
	this->sizeRange = sizeRange;
}

void ParticleEmitter::start() {
	transform = gameObject->getComponent<Transform>();
}

void ParticleEmitter::update() {

	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i]->update();
	}

	if (enabled && (float)(clock() - timeOfPrevSpawn) / CLOCKS_PER_SEC > timeTilNextSpawn) {
		timeOfPrevSpawn = clock();
		timeTilNextSpawn = Utilities::randomFloatInRange(rateRange.x, rateRange.y);

		Vector2 pos = localCenterOffset;
		pos.x += Utilities::randomFloatInRange(-spawnRange.x, spawnRange.x);
		pos.y += Utilities::randomFloatInRange(-spawnRange.y, spawnRange.y);

		Vector2 size;
		size.x = Utilities::randomFloatInRange(sizeRange.x, sizeRange.y);
		size.y = size.x;
		//size = Vector2(.5f, .5f);

		float lifeTime = Utilities::randomFloatInRange(lifeTimeRange.x, lifeTimeRange.y);
		int colorIndex = Utilities::randomIntInRange(0, colors.size() - 1);

		pos = /*Camera::getCameraMatrix() */ transform->getTransformation() * pos;
		//size = /*Camera::getCameraMatrix() */ transform->getTransformation() * size;

		Particle* p = new Particle(this, size, colors[colorIndex], sprite, pos, lifeTime);
		particles.push_back(p);
	}
}

void ParticleEmitter::addColor(const Vector4& color) {
	colors.push_back(color);
}

void ParticleEmitter::remove(Particle* p) {

	auto it = find(particles.begin(), particles.end(), p);
	if (it != particles.end()) {
		particles.erase(it);
	}
}
