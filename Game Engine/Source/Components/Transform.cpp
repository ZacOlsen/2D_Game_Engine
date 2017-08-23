#include "Transform.h"
#include "..\Graphics\Camera.h"
#include "..\Misc\GameManager.h"

unsigned short Transform::idCounter = 0;

Transform::Transform(const Matrix3& trans, const Matrix3& rot, const Matrix3& scale, Transform* parent) {

	id = ++idCounter;

	translation = trans;
	rotation = rot;
	this->scale = scale;

	children = vector<Transform*>();

	if (parent) {
		setParent(parent);
	}

	updateTransform();
}

Transform::~Transform() {}

std::string Transform::getSaveString() {

	string save = "Transform\n";
	save += to_string(id) + "\n";
	if (parent) {
		save += to_string(parent->id);
	} else {
		save += to_string(-1);
	}
	save += "\n";//add parent later
	save += to_string(translation[2][0]) + ", " + to_string(translation[2][1]) + "\n";
	save += to_string(acosf(rotation[0][0])) + "\n";
	save += to_string(scale[0][0]) + ", " + to_string(scale[1][1]) + "\n";

	return save;
}

Transform* Transform::createFromString(const string& string) {

	Transform* trans = new Transform();

	int start = 0;
	int end = string.find('\n', start);
	int id = std::stoi(string.substr(start, end - start));
	trans->id = id;

	start = end + 1;
	end = string.find('\n', start);
	int parentID = std::stoi(string.substr(start, end - start));
	if (parentID > 0) {
		trans->setParent(GameManager::getTransformOfID(parentID));
	} else {
		trans->parent = nullptr;
	}

	start = end + 1;
	end = string.find(',', start);
	float xt = std::stof(string.substr(start, end - start));

	start = end + 2;
	end = string.find('\n', start);
	float yt = std::stof(string.substr(start, end - start));
	trans->setLocaLPosition(xt, yt);

	start = end + 1;
	end = string.find('\n', start);
	float rot = std::stof(string.substr(start, end - start));
	trans->setLocaLRotation(rot);

	start = end + 1;
	end = string.find(',', start);
	float xs = std::stof(string.substr(start, end - start));

	start = end + 2;
	end = string.find('\n', start);
	float ys = std::stof(string.substr(start, end - start));
	trans->setLocaLScale(xs, ys);

	return trans;
}

unsigned short Transform::getID() {
	return id;
}

void Transform::addToLocalPosition(const float& x, const float& y) {

	translation[2].x += x;
	translation[2].y += y;
	updateTransform();
}

void Transform::setLocaLPosition(const float& x, const float& y) {
	
	translation[2].x = x;
	translation[2].y = y;
	updateTransform();
}

void Transform::setLocaLRotation(const float& angle) {

	rotation = Matrix3::rotationMatrix(angle);
	updateTransform();
}

void Transform::setLocaLScale(const float& x, const float& y) {

	scale[0].x = x;
	scale[1].y = y;
	updateTransform();
}

void Transform::updateTransform() {

	if (parent) {
		transformation = parent->transformation * translation * rotation * scale;
	} else {
		transformation = translation * rotation * scale;
	}

	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->updateTransform();
	}
}

Transform* Transform::getRoot() {

	Transform* temp = this;
	while (temp->parent) {
		temp = temp->parent;
	}

	return temp;
}

void Transform::setParent(Transform* parent) {

	if (this->parent) {
		removeParent();
	}

	this->parent = parent;
	parent->children.push_back(this);
}

void Transform::removeParent() {
	
	auto it = find(parent->children.begin(), parent->children.end(), this);
	if (it != parent->children.end()) {
		parent->children.erase(it);
	}

	parent = nullptr;
}

unsigned int Transform::childCount() {
	return children.size();
}

Transform* Transform::getChild(const int& index) {
	return children[index];
}

Matrix3 Transform::getTransformation() {
	return transformation;
}

bool Transform::isInTransformTree(Transform* other) {

	//union find check roots

	Transform* temp = other;
	while (temp) {
		if (temp == this) {
			return true;
		}

		temp = temp->parent;
	}

	temp = this;
	while (temp) {
		if (temp == other) {
			return true;
		}

		temp = temp->parent;
	}

	return false;
}

Vector2 Transform::getWorldPosition() {
	return transformation[2];
}

Vector2 Transform::getLocalScale() {
	return Vector2(scale[0][0], scale[1][1]);
}

void Transform::getWorldPosition(Vector2& vec1, Vector2& vec2, Vector2& vec3, Vector2& vec4) {
	
	vec1 = transformation * vec1;
	vec2 = transformation * vec2;
	vec3 = transformation * vec3;
	vec4 = transformation * vec4;
}

void Transform::getCameraPerspectivePosition(Vector2& vec1, Vector2& vec2, Vector2& vec3, Vector2& vec4) {

	//Matrix3 transform = Camera::transform->transformation * transformation;
	Matrix3 transform = Camera::getCameraMatrix() * transformation;

	vec1 = transform * vec1;
	vec2 = transform * vec2;
	vec3 = transform * vec3;
	vec4 = transform * vec4;
}
