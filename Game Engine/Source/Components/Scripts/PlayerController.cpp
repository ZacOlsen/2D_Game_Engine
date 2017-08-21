#include "PlayerController.h"

string PlayerController::getSaveString() {

	string save = "PlayerController\n";
	save += to_string(speed) + ", " + to_string(jumpAccel) + ", " + to_string(grounded) + ", " + to_string(lives) + "\n";
	save += to_string(spawnPoint.x) + ", " + to_string(spawnPoint.y) + "\n";

	return save;
}

PlayerController* PlayerController::createFromString(const string& str) {

	PlayerController* pc = new PlayerController();

	int start = 0;
	int end = str.find(',', start);
	float speed = std::stof(str.substr(start, end - start));
	pc->speed = speed;

	start = end + 2;
	end = str.find(',', start);
	float jumpAccel = std::stof(str.substr(start, end - start));
	pc->jumpAccel = jumpAccel;

	start = end + 2;
	end = str.find(',', start);
	bool grounded = std::stoi(str.substr(start, end - start));
	pc->grounded = grounded;

	start = end + 2;
	end = str.find('\n', start);
	int lives = std::stoi(str.substr(start, end - start));
	pc->lives = lives;

	start = end + 1;
	end = str.find(',', start);
	float xs = std::stof(str.substr(start, end - start));

	start = end + 2;
	end = str.find('\n', start);
	float ys = std::stof(str.substr(start, end - start));
	pc->spawnPoint = Vector2(xs, ys);

	return pc;
}

void PlayerController::start() {

	text = GameManager::findGameObject("Text")->getComponent<TextRenderer>();
	text->createText(to_string(lives).c_str(), 80);

	rb = gameObject->getComponent<RigidBody>();
	animContr = gameObject->getComponent<AnimatorController>();
	emitter = gameObject->getComponent<ParticleEmitter>();

	using namespace std::placeholders;
	GameManager::findGameObject("Image")->getComponent<Button>()->addReleaseCallback(std::bind(&PlayerController::die, this));
}

void PlayerController::update() {

	float x = 0;

	if (Input::getKeyDown(GLFW_KEY_A)) {
		x += -speed;
		gameObject->transform->setLocaLScale(-1, 1);
	}

	if (Input::getKeyDown(GLFW_KEY_D)) {
		x += speed;
		gameObject->transform->setLocaLScale(1, 1);
	}

	if (grounded && Input::getKeyPressed(GLFW_KEY_SPACE)) {
		jump();
	}

	animContr->changeToAnimation(x != 0 ? "walk" : "idle");
	emitter->enabled = x != 0;

	rb->velocity.x = x;
}

void PlayerController::lateUpdate() {
	Camera::transform->setLocaLPosition(gameObject->transform->getWorldPosition().x, 0);
}

void PlayerController::jump() {
	grounded = false;
	rb->acceleration.y = jumpAccel;
}

void PlayerController::die() {

	lives--;
	text->createText(to_string(lives).c_str(), 80);

	gameObject->transform->setLocaLPosition(spawnPoint.x, spawnPoint.y);
	rb->velocity = Vector2();
}

void PlayerController::onTriggerEnter(BoxCollider* col) {
	grounded = true;
}

void PlayerController::onTriggerStay(BoxCollider* col) {
	grounded = true;
}

void PlayerController::onTriggerExit(BoxCollider* col) {
	grounded = false;
}
