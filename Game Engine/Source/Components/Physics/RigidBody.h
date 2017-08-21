#pragma once

#include "..\Component.h"
#include "..\..\Physics\Physics.h"
#include "..\..\Misc\GameObject.h"

#define TIME_BETWEEN_FRAMES 1.0f / 60.0f

class RigidBody : public Component {

public:
	
	Vector2 velocity;
	Vector2 acceleration;

	RigidBody();
	~RigidBody();

	string getSaveString();
	static RigidBody* createFromString(const string& str);

	Vector2 getPreviousPosition() const;

	friend ostream& operator<<(ostream& stream, const RigidBody& rb);
};

