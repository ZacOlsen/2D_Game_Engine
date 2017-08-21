#include "GameManager.h"

float GameManager::physLagTime = 0;
clock_t GameManager::prevFrame;
vector<GameObject*> GameManager::gameObjects;
Canvas* GameManager::canvas;

void GameManager::init() {

	Renderer::init();
	SpriteRenderer::init();
	gameObjects = vector<GameObject*>();
	Physics::init();
	Physics::debug = true;

	Sprite* backgroundLight = Sprite::getSprite("background light.png");
	Sprite* backgroundDark = Sprite::getSprite("background dark.png");
	vector<Sprite*> set;
	set.push_back(backgroundLight);
	set.push_back(backgroundDark);

	vector<string> locNames;
	locNames.push_back("imageLight");
	locNames.push_back("imageShadow");

	maunalWorldBuild();

	Shader* lightShader = SpriteRenderer::getShader(2);
	GameObject* back = new GameObject("Background");
	back->addComponent(new Transform(Matrix3::translationMatrix(20, 0)));
	back->addComponent(new SpriteRenderer(Vector2(60, 16), Vector4(1, 1, 1, 1), set, locNames, 0));
	back->getComponent<SpriteRenderer>()->setShaderIndex(2);

//	Scene scene("test scene.txt");
//	scene.saveScene(gameObjects);
//	scene.loadScene();

	canvas = findGameObject("Canvas")->getComponent<Canvas>();

	Vector2 rate(.01f, .02f);
	Vector2 life(.25f, .6f);
	Vector2 offset(-.5f, 0);
	Vector2 spawn(.25f, .5f);
	Vector2 size(.25f, .75f);
	ParticleEmitter* pe = new ParticleEmitter(rate, life, offset, spawn, size);
	pe->sprite = Sprite::getSprite("star.png");
	pe->addColor(Vector4(1, 0, 0, 1));
	pe->addColor(Vector4(0, 1, 0, 1));
	pe->addColor(Vector4(0, 0, 1, 1));
	findGameObject("Player")->addComponent(pe);

//	Sprite* shadow = Sprite::getSprite("theif shadow.png");

	lightShader->enable();
	lightShader->setUniform2f(Vector2(0, -5), "light");
	lightShader->setUniform4f(Vector4(1, 1, 1, 1), "lightColor");
	lightShader->setUniform1f(2, "brightness");
//	lightShader->setUniform1i(shadow->textureID, "imageShadow");
	findGameObject("Player")->getComponent<SpriteRenderer>()->setShaderIndex(2);
	lightShader->disable();

	vector<Sprite*> set1;
	set1.push_back(Sprite::getSprite("wolfwalk1.png"));
	vector<Sprite*> set2;
	set2.push_back(Sprite::getSprite("wolfwalk2.png"));
	vector<vector<Sprite*>> sprites;
	sprites.push_back(set1);
	sprites.push_back(set2);
	Animation* anim = new Animation(sprites, .5f, "walking");
	vector<Animation*> anims;
	anims.push_back(anim);

	GameObject* wolf = new GameObject("Wolf");
	wolf->addComponent(new Transform(Matrix3::translationMatrix(30, -5)));
	wolf->addComponent(new RigidBody());
	wolf->addComponent(new BoxCollider(Vector2(1, 1)));
	wolf->addComponent(new SpriteRenderer(Vector2(1, 1), Vector4(1, 1, 1, 1), Sprite::getSprite("wolfwalk1.png")));
	wolf->addComponent(new AnimatorController(anims));
	wolf->addComponent(new WolfController());

	GameObject* head = new GameObject("Head Check");
	head->addComponent(new Transform(Matrix3::translationMatrix(0, .5f),
		Matrix3::identityMatrix(), Matrix3::identityMatrix(), wolf->transform));
	head->addComponent(new BoxCollider(Vector2(.99f, .02f), true));

	onStart();

	prevFrame = clock();
}

void GameManager::maunalWorldBuild() {

	Sprite* groundTile = new Sprite("repeatable wall.png");
	Sprite* playerSprite = new Sprite("color test.png");
	Sprite* towerSprite = new Sprite("tower.png");
	for (float i = 0; i < 60; i++) {

		if (i == 17) {
			i += 3;
		}

		GameObject* ground = new GameObject("Ground");
		ground->addComponent(new Transform(Matrix3::translationMatrix(i - 8, -6)));
		ground->addComponent(new SpriteRenderer(Vector2(1, 1), Vector4(1, 0, 0, 1), groundTile));
		ground->addComponent(new BoxCollider(Vector2(1, 1)));
	}

	buildPiramid(4.5f, -5);
	buildPiramid(15.5f, -5, -1);

	GameObject* tower = new GameObject("Tower");
	tower->addComponent(new Transform(Matrix3::translationMatrix(25, -4)));
	tower->addComponent(new SpriteRenderer(Vector2(3, 3), Vector4(0, 0, 1, 1), towerSprite));
	tower->addComponent(new BoxCollider(Vector2(3, 3)));

	tower = new GameObject("Tower");
	tower->addComponent(new Transform(Matrix3::translationMatrix(35, -4)));
	tower->addComponent(new SpriteRenderer(Vector2(3, 3), Vector4(0, 1, 0, 1), towerSprite));
	tower->addComponent(new BoxCollider(Vector2(3, 3)));

	vector<Sprite*> idleSet1;
	idleSet1.push_back(new Sprite("theif light idle1.png"));
	idleSet1.push_back(new Sprite("theif shadow idle1.png"));

	vector<Sprite*> idleSet2;
	idleSet2.push_back(new Sprite("theif light idle2.png"));
	idleSet2.push_back(new Sprite("theif shadow idle2.png"));

	vector<vector<Sprite*>> idle;
	idle.push_back(idleSet1);
	idle.push_back(idleSet2);
	Animation* anim1 = new Animation(idle, .5f, "idle");

	vector<Sprite*> walkSet1;
	walkSet1.push_back(new Sprite("theif light walk1.png"));
	walkSet1.push_back(new Sprite("theif shadow walk1.png"));

	vector<Sprite*> walkSet2;
	walkSet2.push_back(new Sprite("theif light walk2.png"));
	walkSet2.push_back(new Sprite("theif shadow walk2.png"));

	vector<vector<Sprite*>> walk;
	walk.push_back(walkSet1);
	walk.push_back(walkSet2);
	Animation* anim2 = new Animation(walk, .5f, "walk");

	vector<Animation*> anims;
	anims.push_back(anim1);
	anims.push_back(anim2);
	vector<string> locNames;
	locNames.push_back("imageLight");
	locNames.push_back("imageShadow");

	GameObject* box = new GameObject("Player");
	box->addComponent(new Transform(Matrix3::translationMatrix(0, .75f)));
	box->addComponent(new SpriteRenderer(Vector2(1, 1), Vector4(1, 1, 1, 1), idleSet1, locNames));
	box->addComponent(new RigidBody());
	box->addComponent(new BoxCollider(Vector2(1, 1)));
	box->addComponent(new PlayerController());
	box->addComponent(new AnimatorController(anims, 0));

	GameObject* groundCheck = new GameObject("Ground Check");
	groundCheck->addComponent(new Transform(Matrix3::translationMatrix(0, -.5f),
		Matrix3::identityMatrix(), Matrix3::identityMatrix(), box->transform));
	groundCheck->addComponent(new BoxCollider(Vector2(.99f, .02f), true));

	GameObject* deathBox = new GameObject("Death Box");
	deathBox->addComponent(new Transform(Matrix3::translationMatrix(10, -10)));
	deathBox->addComponent(new BoxCollider(Vector2(100, 1), true));
	deathBox->addComponent(new DeathBox());

	GameObject* can = new GameObject("Canvas");
	can->addComponent(new RectTransform(Matrix3::identityMatrix(), Matrix3::identityMatrix(),
		Matrix3::scaleMatrix(2.0f / (float)Camera::getWidth(), 2.0f / (float)Camera::getHeight())));
	can->addComponent(new Canvas());
	canvas = can->getComponent<Canvas>();

	GameObject* canChild = new GameObject("Image");
	canChild->addComponent(new RectTransform(Matrix3::translationMatrix(-380, 170), Matrix3::identityMatrix(),
		Matrix3::scaleMatrix(100, 100), (RectTransform*)can->transform));
	canChild->addComponent(new Renderer(Vector4(1, 1, 1, 1), playerSprite));
	canChild->addComponent(new Button());

	GameObject* text = new GameObject("Text");
	text->addComponent(new RectTransform(Matrix3::translationMatrix(450, 170), Matrix3::identityMatrix(),
		Matrix3::identityMatrix(), (RectTransform*)can->transform));
	text->addComponent(new TextRenderer("-phaser-@", 80, RIGHT, Vector4(.8f, .2f, .8f, 1)));
}

void GameManager::buildPiramid(const float& startx, const float& starty, const float& direction) {

	Sprite* groundTile = new Sprite("repeatable wall.png");
	for (float i = 0; i < 4; i++) {
		GameObject* ground = new GameObject("Ground");
		ground->addComponent(new Transform(Matrix3::translationMatrix(direction * i + startx, starty)));
		ground->addComponent(new SpriteRenderer(Vector2(1, 1), Vector4(1, 1, 1, 1), groundTile));
		ground->addComponent(new BoxCollider(Vector2(1, 1)));
	}

	for (float i = 0; i < 3; i++) {
		GameObject* ground = new GameObject("Ground");
		ground->addComponent(new Transform(Matrix3::translationMatrix(direction * i + startx + 1.5f * direction, starty + 1)));
		ground->addComponent(new SpriteRenderer(Vector2(1, 1), Vector4(1, 1, 1, 1), groundTile));
		ground->addComponent(new BoxCollider(Vector2(1, 1)));
	}

	for (float i = 0; i < 2; i++) {
		GameObject* ground = new GameObject("Ground");
		ground->addComponent(new Transform(Matrix3::translationMatrix(direction * i + startx + 2 * direction, starty + 2)));
		ground->addComponent(new SpriteRenderer(Vector2(1, 1), Vector4(1, 1, 1, 1), groundTile));
		ground->addComponent(new BoxCollider(Vector2(1, 1)));
	}

	GameObject* ground = new GameObject("Ground");
	ground->addComponent(new Transform(Matrix3::translationMatrix(startx + 3.5f * direction, starty + 3)));
	ground->addComponent(new SpriteRenderer(Vector2(1, 1), Vector4(1, 1, 1, 1), groundTile));
	ground->addComponent(new BoxCollider(Vector2(1, 1)));

	Sprite* groundLeft = new Sprite("wall left half end.png");
	Sprite* groundRight = new Sprite("wall right half end.png");

	GameObject* halfR = new GameObject("Ground");
	halfR->addComponent(new Transform(Matrix3::translationMatrix(startx + 3.75f * direction, starty)));
	halfR->addComponent(new SpriteRenderer(Vector2(.5f, 1), Vector4(1, 1, 1, 1), direction > 0 ? groundRight : groundLeft));
	halfR->addComponent(new BoxCollider(Vector2(.5f, 1)));

	halfR = new GameObject("Ground");
	halfR->addComponent(new Transform(Matrix3::translationMatrix(startx + 3.75f * direction, starty + 2)));
	halfR->addComponent(new SpriteRenderer(Vector2(.5f, 1), Vector4(1, 1, 1, 1), direction > 0 ? groundRight : groundLeft));
	halfR->addComponent(new BoxCollider(Vector2(.5f, 1)));

	GameObject* halfL = new GameObject("Ground");
	halfL->addComponent(new Transform(Matrix3::translationMatrix(startx + .75f * direction, starty + 1)));
	halfL->addComponent(new SpriteRenderer(Vector2(.5f, 1), Vector4(1, 1, 1, 1), direction < 0 ? groundRight : groundLeft));
	halfL->addComponent(new BoxCollider(Vector2(.5f, 1)));

	halfL = new GameObject("Ground");
	halfL->addComponent(new Transform(Matrix3::translationMatrix(startx + 2.75f * direction, starty + 3)));
	halfL->addComponent(new SpriteRenderer(Vector2(.5f, 1), Vector4(1, 1, 1, 1), direction < 0 ? groundRight : groundLeft));
	halfL->addComponent(new BoxCollider(Vector2(.5f, 1)));
}

void GameManager::addGameObject(GameObject* go) {
	gameObjects.push_back(go);
}

void GameManager::removeGameObject(GameObject* go) {

	auto it = find(gameObjects.begin(), gameObjects.end(), go);
	if (it != gameObjects.end()) {
		gameObjects.erase(it);
	}
}

GameObject* GameManager::findGameObject(const char* tag) {

	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		if (!strcmp(gameObjects[i]->tag.c_str(), tag)) {
			return gameObjects[i];
		}
	}

	return nullptr;
}

void GameManager::onStart() {

	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->runStart();
	}
}

void GameManager::onFrame() {

	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->runUpdateables();
	}
	
	Input::update();

	physLagTime += (float(clock() - prevFrame)) / CLOCKS_PER_SEC;
	
	while (physLagTime > TIME_BETWEEN_FRAMES) {
		Physics::applyGravityToRigidbodies();
		Physics::moveRigidBodies();

		physLagTime -= TIME_BETWEEN_FRAMES;
	}
	
	prevFrame = clock();

	Physics::checkAllCollisions();
	
	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->runLateUpdateables();
	}

	Camera::calculateCameraMatrix();
	SpriteRenderer::renderAllSprites();

	if (Physics::debug) {
		Physics::renderColliders();
	}

	canvas->renderUI();

	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i]->checkForDestroy()) {
			i--;
		}
	}
}

Transform* GameManager::getTransformOfID(const unsigned short& id) {

	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i]->transform && gameObjects[i]->transform->getID() == id) {
			return gameObjects[i]->transform;
		}
	}

	return nullptr;
}
