#pragma once

#include <vector>
#include "..\Updateable.h"
#include "..\..\Misc\GameObject.h"

#define NUM_OF_CORNERS 4

class RigidBody;

enum CollisionType {
	ENTER,
	STAY,
	EXIT,
	NONE
};

class BoxCollider : public Updateable {

public:
	
	const unsigned short id;
	bool trigger = false;
	Vector2 size;
	RigidBody* rb = nullptr;

	BoxCollider(const Vector2& size = Vector2(0, 0), const bool& trigger = false);
	~BoxCollider();

	void start();

	std::string getSaveString();
	static BoxCollider* createFromString(const string& str);

	const float checkVerticalCollision(const float& distance, BoxCollider& other) const;
	const float checkHorizontalCollision(const float& distance, BoxCollider& other) const;
	
	const bool checkPointCollision(const float& x, const float& y) const;
	const float checkLineCollision(const Vector2& origin, const Vector2& end) const; //distance to col, < 0 = no col

	const CollisionType checkCollision(BoxCollider& other);
	void fixCollision(const BoxCollider& other);

	friend ostream& operator<<(ostream& stream, const BoxCollider& box);

	void renderBoxCollider() const;

private:

	static unsigned short counter;
	vector<unsigned short> collidingIDs;

	void removeCollisionID(BoxCollider& other);
};

