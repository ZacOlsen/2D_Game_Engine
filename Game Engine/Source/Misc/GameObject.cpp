#include "GameObject.h"

GameObject::GameObject(const string& tag) : tag(tag) {

	//updateable = vector<Updateable*>();
	GameManager::addGameObject(this);
}

GameObject::~GameObject() {

	for (unsigned int i = 0; i < transform->childCount(); i++) {
		delete transform->getChild(i)->gameObject;
	}

	for (unsigned int i = 0; i < components.size(); i++) {
		delete components[i];
	}

	GameManager::removeGameObject(this);
}

string GameObject::getSaveString() {
	
	string save = "GameObject\n";
	save += tag + "\n";
	for (unsigned int i = 0; i < components.size(); i++) {
		save += components[i]->getSaveString();
	}

//	save += "\n";
	return save;
}

GameObject* GameObject::createFromString(const string& string) {

	GameObject* go = new GameObject(string.substr(0, string.length() - 1));
	return go;
}

void GameObject::runStart() {
	
	for (unsigned int i = 0; i < updateables.size(); i++) {
		updateables[i]->start();
	}
}

void GameObject::runUpdateables() {
	
	for (unsigned int i = 0; i < updateables.size(); i++) {
		updateables[i]->update();
	}
}

void GameObject::runLateUpdateables() {

	for (unsigned int i = 0; i < updateables.size(); i++) {
		updateables[i]->lateUpdate();
	}
}

void GameObject::onCollisionEnterCallBack(BoxCollider* col) {
	
	for (unsigned int i = 0; i < updateables.size(); i++) {
		updateables[i]->onCollisionEnter(col);
	}

	if (transform->parent) {
		transform->parent->gameObject->onCollisionEnterCallBack(col);
	}
}

void GameObject::onCollisionStayCallBack(BoxCollider* col) {

	for (unsigned int i = 0; i < updateables.size(); i++) {
		updateables[i]->onCollisionStay(col);
	}

	if (transform->parent) {
		transform->parent->gameObject->onCollisionStayCallBack(col);
	}
}

void GameObject::onCollisionExitCallBack(BoxCollider* col) {

	for (unsigned int i = 0; i < updateables.size(); i++) {
		updateables[i]->onCollisionExit(col);
	}

	if (transform->parent) {
		transform->parent->gameObject->onCollisionExitCallBack(col);
	}
}

void GameObject::onTriggerEnterCallBack(BoxCollider* col) {
	
	for (unsigned int i = 0; i < updateables.size(); i++) {
		updateables[i]->onTriggerEnter(col);
	}
	
	if (transform && transform->parent) {
		transform->parent->gameObject->onTriggerEnterCallBack(col);
	}
}

void GameObject::onTriggerStayCallBack(BoxCollider* col) {

	for (unsigned int i = 0; i < updateables.size(); i++) {
		updateables[i]->onTriggerStay(col);
	}

	if (transform->parent) {
		transform->parent->gameObject->onTriggerStayCallBack(col);
	}
}

void GameObject::onTriggerExitCallBack(BoxCollider* col) {

	for (unsigned int i = 0; i < updateables.size(); i++) {
		updateables[i]->onTriggerExit(col);
	}

	if (transform->parent) {
		transform->parent->gameObject->onTriggerExitCallBack(col);
	}
}

void GameObject::addComponent(Component* comp) {
	
	components.push_back(comp);
	comp->gameObject = this;

	if (dynamic_cast<Updateable*>(comp)) {
		updateables.push_back((Updateable*)comp);
	}

	if (dynamic_cast<Transform*>(comp)) {
		transform = (Transform*)comp;
	}

	if (dynamic_cast<BoxCollider*>(comp)) {
		((BoxCollider*)comp)->rb = getComponent<RigidBody>();
	}
}

void GameObject::removeComponent(Component* comp) {

	auto itc = find(components.begin(), components.end(), comp);
	if (itc != components.end()) {
		components.erase(itc);
	}

	if (dynamic_cast<Updateable*>(comp)) {
		auto itu = find(updateables.begin(), updateables.end(), (Updateable*)comp);
		if (itu != updateables.end()) {
			updateables.erase(itu);
		}
	}
	
	if (dynamic_cast<Transform*>(comp)) {
		transform = nullptr;
	}
}

void GameObject::destroy() {
	shouldDestroy = true;
}

bool GameObject::checkForDestroy() {

	bool destroyed = false;

	if (shouldDestroy) {
		destroyed = true;
		delete this;
	}

	return destroyed;
}
