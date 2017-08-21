#pragma once

#include <cfloat>
#include <vector>
#include "..\Misc\GameObject.h"

#define PHYSICS_EPSILON .0001f

class BoxCollider;
class RigidBody;

class Physics {

public:	

	static bool debug;
	const static Vector2 gravity;
	
	static void init();

	static void applyGravityToRigidbodies();
	static void moveRigidBodies();
	static void checkAllCollisions();

	static void renderColliders();

	static void addRigidBody(RigidBody* rb);
	static void addCollider(BoxCollider* col);

	static void removeRigidBody(RigidBody* rb);
	static void removeCollider(BoxCollider* col);

	static BoxCollider* Raycast(const Vector2& origin, const Vector2& direction, const float& length);
	static vector<BoxCollider*> RaycastAll(const Vector2& origin, const Vector2& direction, const float& length);

private:
	static vector<BoxCollider*> colliders;
	static vector<RigidBody*> rigidbodies;
};