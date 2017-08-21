#include "Physics.h"

bool Physics::debug;
vector<RigidBody*> Physics::rigidbodies;
vector<BoxCollider*> Physics::colliders;
const Vector2 Physics::gravity = Vector2(0.0f, -9.8f);

void Physics::init() {
	rigidbodies = vector<RigidBody*>();
	colliders = vector<BoxCollider*>();
}

void Physics::applyGravityToRigidbodies() {

	for (unsigned int i = 0; i < rigidbodies.size(); i++) {
		rigidbodies[i]->acceleration += gravity * 4;
	}
}

void Physics::moveRigidBodies() {
	
	for (unsigned int i = 0; i < rigidbodies.size(); i++) {

		rigidbodies[i]->velocity += rigidbodies[i]->acceleration * TIME_BETWEEN_FRAMES;

		float yDelta = rigidbodies[i]->velocity.y * TIME_BETWEEN_FRAMES;
		float xDelta = rigidbodies[i]->velocity.x * TIME_BETWEEN_FRAMES;

		BoxCollider* currentCol = rigidbodies[i]->gameObject->getComponent<BoxCollider>();

		for (unsigned int j = 0; j < colliders.size(); j++) {

			if (rigidbodies[i]->gameObject->transform->isInTransformTree(colliders[j]->gameObject->transform)) {
				continue;
			}

			if (!colliders[j]->trigger && !currentCol->trigger) {
				yDelta = currentCol->checkVerticalCollision(yDelta, *colliders[j]);
			}
		}

		if (yDelta != rigidbodies[i]->velocity.y * TIME_BETWEEN_FRAMES) {
			rigidbodies[i]->velocity.y = 0;
		}

		rigidbodies[i]->gameObject->transform->addToLocalPosition(0, yDelta);

		for (unsigned int j = 0; j < colliders.size(); j++) {

			if (rigidbodies[i]->gameObject->transform->isInTransformTree(colliders[j]->gameObject->transform)) {
				continue;
			}
			
			if (!colliders[j]->trigger && !currentCol->trigger) {
				xDelta = currentCol->checkHorizontalCollision(xDelta, *colliders[j]);
			}
		}

		if (xDelta != rigidbodies[i]->velocity.x * TIME_BETWEEN_FRAMES) {
			rigidbodies[i]->velocity.x = 0;
		}

		rigidbodies[i]->gameObject->transform->addToLocalPosition(xDelta, 0);
		rigidbodies[i]->acceleration = Vector2();
	}
}

void Physics::checkAllCollisions() {

	for (unsigned int i = 0; i < colliders.size(); i++) {
		for (unsigned int j = i + 1; j < colliders.size(); j++) {

			if (colliders[i]->gameObject->transform->isInTransformTree(colliders[j]->gameObject->transform)) {
				continue;
			}

			CollisionType colType = NONE;
			
			if (colliders[i]->rb || colliders[j]->rb) {
				colType = colliders[i]->checkCollision(*colliders[j]);
			}

			switch (colType) {

			case ENTER:

				if (colliders[i]->trigger) {
					colliders[i]->gameObject->onTriggerEnterCallBack(colliders[j]);
				} else {
					colliders[i]->gameObject->onCollisionEnterCallBack(colliders[j]);
				}

				if (colliders[j]->trigger) {
					colliders[j]->gameObject->onTriggerEnterCallBack(colliders[i]);
				} else {
					colliders[j]->gameObject->onCollisionEnterCallBack(colliders[i]);
				}

				break;
			
			case STAY:

				if (colliders[i]->trigger) {
					colliders[i]->gameObject->onTriggerStayCallBack(colliders[j]);
				} else {
					colliders[i]->gameObject->onCollisionStayCallBack(colliders[j]);
				}

				if (colliders[j]->trigger) {
					colliders[j]->gameObject->onTriggerStayCallBack(colliders[i]);
				} else {
					colliders[j]->gameObject->onCollisionStayCallBack(colliders[i]);
				}

				break;

			case EXIT:

				if (colliders[i]->trigger) {
					colliders[i]->gameObject->onTriggerExitCallBack(colliders[j]);
				} else {
					colliders[i]->gameObject->onCollisionExitCallBack(colliders[j]);
				}

				if (colliders[j]->trigger) {
					colliders[j]->gameObject->onTriggerExitCallBack(colliders[i]);
				} else {
					colliders[j]->gameObject->onCollisionExitCallBack(colliders[i]);
				}

				break;

			case NONE:
				break;
			}
		}
	}
}

void Physics::renderColliders() {

	for (unsigned int i = 0; i < colliders.size(); i++) {
		colliders[i]->renderBoxCollider();
	}
}

void Physics::addRigidBody(RigidBody* rb) {
	rigidbodies.push_back(rb);
}

void Physics::addCollider(BoxCollider* col) {
	colliders.push_back(col);
}

void Physics::removeRigidBody(RigidBody* rb) {

	auto it = find(rigidbodies.begin(), rigidbodies.end(), rb);
	if (it != rigidbodies.end()) {
		rigidbodies.erase(it);
	}
}

void Physics::removeCollider(BoxCollider* col) {

	auto it = find(colliders.begin(), colliders.end(), col);
	if (it != colliders.end()) {
		colliders.erase(it);
	}
}

BoxCollider* Physics::Raycast(const Vector2& origin, const Vector2& direction, const float& length) {

	const Vector2 end = direction.normalized() * length + origin;

	float shortestDist = FLT_MAX;
	int index = -1;
	for (unsigned int i = 0; i < colliders.size(); i++) {

		float dist = colliders[i]->checkLineCollision(origin, end);
		if (dist >= 0 && dist < shortestDist) {

			if (dist == 0) {
				return colliders[i];
			}

			shortestDist = dist;
			index = i;
		}
	}

	return index < 0 ? nullptr : colliders[index];
}

vector<BoxCollider*> Physics::RaycastAll(const Vector2& origin, const Vector2& direction, const float& length) {
	
	const Vector2 end = direction.normalized() * length + origin;
	vector<BoxCollider*> collisions;

	for (unsigned int i = 0; i < colliders.size(); i++) {
		if (colliders[i]->checkLineCollision(origin, end) >= 0) {
			collisions.push_back(colliders[i]);
		}
	}

	return collisions;
}
