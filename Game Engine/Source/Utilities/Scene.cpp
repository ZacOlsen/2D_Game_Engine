#include "Scene.h"

Scene::Scene(const char* name) {
	this->name = name;
}

Scene::~Scene() {}

void Scene::saveScene(const vector<GameObject*>& gameObjects) {

	string save = "";
	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		save += gameObjects[i]->getSaveString();
	}

	Utilities::writeToFile(name, save);
}

void Scene::loadScene() {

	string scene = Utilities::readFile(name);

	unsigned int start = 0;
	unsigned int end = scene.find('\n', start);

	string type = scene.substr(start, end);
	
	while (type == "GameObject") {
		start = end + 1;
		end = scene.find('\n', start) + 1;
		GameObject* go = GameObject::createFromString(scene.substr(start, end - start));
		//cout << go->getSaveString();

		start = end;
		end = scene.find('\n', start);
		type = scene.substr(start, end - start);

		while (type == "Transform" || type == "SpriteRenderer" || type == "BoxCollider" ||
			type == "RigidBody" || type == "AnimatorController" || type == "Animation" ||
			type == "PlayerController" || type == "DeathBox" || type == "Canvas" || 
			type == "Renderer" || type == "Button" || type == "TextRenderer" || type == "RectTransform") {

			start = end + 1;
			end = start;
			
			if (type == "Transform") {
				for (int i = 0; i < 5; i++) {
					end = scene.find('\n', end) + 1;
				}
				Transform* trans = Transform::createFromString(scene.substr(start, end - start));
				//cout << trans->getSaveString();
				go->addComponent(trans);

			} else if (type == "RectTransform") {
				for (int i = 0; i < 5; i++) {
					end = scene.find('\n', end) + 1;
				}
				RectTransform* trans = RectTransform::createFromString(scene.substr(start, end - start));
				//cout << trans->getSaveString();
				go->addComponent(trans);

			} else if (type == "SpriteRenderer") {
				for (int i = 0; i < 3; i++) {
					end = scene.find('\n', end) + 1;
				}
				SpriteRenderer* sr = SpriteRenderer::createFromString(scene.substr(start, end - start));
				//cout << sr->getSaveString();
				go->addComponent(sr);

			} else if (type == "BoxCollider") {
				for (int i = 0; i < 2; i++) {
					end = scene.find('\n', end) + 1;
				}
				BoxCollider* box = BoxCollider::createFromString(scene.substr(start, end - start));
				//cout << box->getSaveString();
				go->addComponent(box);

			} else if (type == "RigidBody"){
				RigidBody* rb = new RigidBody();
				//cout << rb->getSaveString();
				go->addComponent(rb);

			} else if (type == "AnimatorController") {
				end = scene.find('\n', start) + 1;
				AnimatorController* anim = AnimatorController::createFromString(scene.substr(start, end - start));
				//cout << anim->getSaveString();
				go->addComponent(anim);

			} else if (type == "Animation") {
				for (int i = 0; i < 3; i++) {
					end = scene.find('\n', end) + 1;
				}
				Animation* anim = Animation::createFromString(scene.substr(start, end - start));
				//cout << anim->getSaveString();
				go->getComponent<AnimatorController>()->addAnimation(anim);
			
			} else if (type == "PlayerController") {
				for (int i = 0; i < 2; i++) {
					end = scene.find('\n', end) + 1;
				}
				PlayerController* pc = PlayerController::createFromString(scene.substr(start, end - start));
				//cout << pc->getSaveString();
				go->addComponent(pc);

			} else if (type == "DeathBox") {
				DeathBox* db = new DeathBox();
				//cout << db->getSaveString();
				go->addComponent(db);

			} else if (type == "Canvas") {
				Canvas* can = new Canvas();
				//cout << can->getSaveString();
				go->addComponent(can);

			} else if (type == "Renderer") {
				for (int i = 0; i < 2; i++) {
					end = scene.find('\n', end) + 1;
				}
				Renderer* rend = Renderer::createFromString(scene.substr(start, end - start));
				//cout << rend->getSaveString();
				go->addComponent(rend);

			} else if (type == "Button") {
				end = scene.find('\n', end) + 1;
				Button* but = Button::createFromString(scene.substr(start, end - start));
				//cout << but->getSaveString();
				go->addComponent(but);

			} else if (type == "TextRenderer") {
				for (int i = 0; i < 4; i++) {
					end = scene.find('\n', end) + 1;
				}
				TextRenderer* text = TextRenderer::createFromString(scene.substr(start, end - start));
				//cout << text->getSaveString();
				go->addComponent(text);
			}

			start = end;
			end = scene.find('\n', start);
			type = scene.substr(start, end - start);
		}
	}
}
