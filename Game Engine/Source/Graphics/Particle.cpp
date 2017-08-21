#include "Particle.h"
#include "..\Components\Graphics\ParticleEmitter.h"

Particle::Particle(ParticleEmitter* emitter, const Vector2& size, const Vector4& color,
	Sprite* sprite, const Vector2& pos, const float& lifeTime) : SpriteRenderer(size, color, sprite) {

	this->emitter = emitter;
	this->pos = pos;
	this->lifeTime = lifeTime;

	timeOfSpawn = clock();

//	m_shader = &shaderUI;
}

Particle::~Particle() {

	emitter->remove(this);

	auto it = find(spriteRenders.begin(), spriteRenders.end(), this);
	if (it != spriteRenders.end()) {
		spriteRenders.erase(it);
	}
}

void Particle::update() {

	if ((float)(clock() - timeOfSpawn) / CLOCKS_PER_SEC > lifeTime) {
		delete this;
	}
}

void Particle::render() {

	float top = size.y / 2.0f + pos.y;
	float bot = -size.y / 2.0f + pos.y;
	float left = -size.x / 2.0f + pos.x;
	float right = size.x / 2.0f + pos.x;

	Vector2 topR = Camera::getCameraMatrix() * Vector2(right, top);
	Vector2 topL = Camera::getCameraMatrix() * Vector2(left, top);
	Vector2 botL = Camera::getCameraMatrix() * Vector2(left, bot);
	Vector2 botR = Camera::getCameraMatrix() * Vector2(right, bot);

	sprite->bind();
	Renderer::renderSprite(botL, botR, topR, topL);
	sprite->unbind();
}
