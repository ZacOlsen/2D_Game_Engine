#include "RectTransform.h"
#include "..\..\Misc\GameManager.h"

RectTransform::RectTransform(const Matrix3& trans, const Matrix3& rot, const Matrix3& scale, RectTransform* parent) {
	
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

string RectTransform::getSaveString() {

	string save = "RectTransform\n";
	save += to_string(id) + "\n";
	if (parent) {
		save += to_string(((RectTransform*)parent)->id);
	} else {
		save += to_string(-1);
	}
	save += "\n";//add parent later
	save += to_string(translation[2][0]) + ", " + to_string(translation[2][1]) + "\n";
	save += to_string(acosf(rotation[0][0])) + "\n";
	save += to_string(scale[0][0]) + ", " + to_string(scale[1][1]) + "\n";

	return save;
}

RectTransform* RectTransform::createFromString(const string& string) {

	RectTransform* trans = new RectTransform();

	int start = 0;
	int end = string.find('\n', start);
	int id = std::stoi(string.substr(start, end - start));
	trans->id = id;

	start = end + 1;
	end = string.find('\n', start);
	int parentID = std::stoi(string.substr(start, end - start));
	if (parentID > 0) {
		trans->setParent((RectTransform*)GameManager::getTransformOfID(parentID));
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

void RectTransform::setParent(RectTransform* parent) {

	if (this->parent) {
		removeParent();
	}

	this->parent = parent;
	parent->children.push_back(this);
}

RectTransform* RectTransform::getChild(const int& index) {
	return (RectTransform*)children[index];
}

void RectTransform::getCameraPerspectivePosition(Vector2& vec1, Vector2& vec2, Vector2& vec3, Vector2& vec4) {

	vec1 = transformation * vec1;
	vec2 = transformation * vec2;
	vec3 = transformation * vec3;
	vec4 = transformation * vec4;
}
