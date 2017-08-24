#pragma once

#include "..\Components\Updateable.h"
#include "..\Components\UI\RectTransform.h"
#include "..\Components\Physics\BoxCollider.h"
#include "..\Components\Physics\RigidBody.h"
#include "..\Components\Graphics\SpriteRenderer.h"
#include "..\Components\Graphics\TextRenderer.h"
#include "..\Components\UI\Canvas.h"
#include "..\Components\Graphics\AnimatorController.h"
#include "..\Components\UI\Button.h"
#include "..\Components\Graphics\ParticleEmitter.h"
#include "..\Components\Scripts\WolfController.h"
#include "GameManager.h"

class GameObject {

public:

	const string tag;
	Transform* transform = nullptr;
	
	GameObject(const string& tag = "untagged");
	~GameObject();

	string getSaveString();
	static GameObject* createFromString(const string& string);

	void runStart();
	void runUpdateables();
	void runLateUpdateables();

	void onCollisionEnterCallBack(BoxCollider* col);
	void onCollisionStayCallBack(BoxCollider* col);
	void onCollisionExitCallBack(BoxCollider* col);
		 
	void onTriggerEnterCallBack(BoxCollider* col);
	void onTriggerStayCallBack(BoxCollider* col);
	void onTriggerExitCallBack(BoxCollider* col);

	void addComponent(Component* comp);
	template<class T> T* getComponent() const;
	void removeComponent(Component* comp);

	void destroy();
	bool checkForDestroy();

private:

	bool shouldDestroy = false;
	vector<Component*> components;
	vector<Updateable*> updateables;
};

template<class T> T* GameObject::getComponent() const {

	for (unsigned int i = 0; i < components.size(); i++) {
		if (dynamic_cast<T*>(components[i])) {
			return (T*)components[i];
		}
	}

	if (transform->getParent()) {
		return transform->getParent()->gameObject->getComponent<T>();
	}

	return nullptr;
}
