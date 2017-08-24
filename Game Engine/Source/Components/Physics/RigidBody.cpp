#include "RigidBody.h"

RigidBody::RigidBody() {
	Physics::addRigidBody(this);
}

RigidBody::~RigidBody() {
	Component::~Component();
	Physics::removeRigidBody(this);
}

string RigidBody::getSaveString() {

	string save = "RigidBody\n";
	return save;
}

RigidBody* RigidBody::createFromString(const string& str) {
	return new RigidBody();
}

const Vector2 RigidBody::getPreviousPosition() const {
	return gameObject->transform->getTransformation()[2] - velocity * TIME_BETWEEN_FRAMES;
}

ostream& operator<<(ostream& stream, const RigidBody& rb) {

	stream << "RigidBody:" << endl;
	stream << "Velocity " << rb.velocity << endl;
	stream << "Acceleration " << rb.acceleration << endl;
	stream << "Position " << rb.gameObject->transform->getTransformation()[2] << endl;
	stream << "Previous " << rb.getPreviousPosition() << endl;

	return stream;
}
