#include "AnimatorController.h"
#include "..\..\Misc\GameObject.h"

AnimatorController::AnimatorController(const vector<Animation*> animations)
	: AnimatorController(animations, 0) {}

AnimatorController::AnimatorController(const vector<Animation*> animations, const char*& startAnimName) {
	this->animations = animations;
	changeToAnimation(startAnimName);
}

AnimatorController::AnimatorController(const vector<Animation*> animations, const unsigned int& startAnimIndex) {
	this->animations = animations;
	animIndex = startAnimIndex;
}

string AnimatorController::getSaveString() {

	string save = "AnimatorController\n";
	save += to_string(animIndex) + "\n";
	
	for (unsigned int i = 0; i < animations.size(); i++) {
		save += animations[i]->getSaveString();
	}

//	save += "\n";
	return save;
}

AnimatorController* AnimatorController::createFromString(const string& str) {

	int start = 0;
	int end = str.find('\n', start);
	int startIn = std::stoi(str.substr(start, end - start));

	vector<Animation*> anims;
	return new AnimatorController(anims, startIn);
}

void AnimatorController::start() {
	
	renderer = gameObject->getComponent<Renderer>();
	renderer->sprite = animations[animIndex]->getSprite(spriteIndex);
	timer = clock();
}

void AnimatorController::update() {

	if ((float)(clock() - timer) / CLOCKS_PER_SEC >= animations[animIndex]->frameRate) {
		timer = clock();

		spriteIndex++;
		if (spriteIndex >= animations[animIndex]->spriteCount()) {
			spriteIndex = 0;
		}

		renderer->sprite = animations[animIndex]->getSprite(spriteIndex);
	}
}

void AnimatorController::addAnimation(Animation* anim) {
	animations.push_back(anim);
}

void AnimatorController::changeToAnimation(const char* name) {

	for (unsigned int i = 0; i < animations.size(); i++) {		
		if (!strcmp(animations[i]->name, name)) {

			if (i == animIndex) {
				break;
			}

			animIndex = i;
			spriteIndex = 0;
			renderer->sprite = animations[animIndex]->getSprite(spriteIndex);
			timer = clock();
			break;
		}
	}
}
