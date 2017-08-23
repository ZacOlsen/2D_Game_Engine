#pragma once

#include <vector>
#include "Component.h"

class Transform : public Component {

public:

	Transform* parent = nullptr;

	Transform(const Matrix3& trans = Matrix3::identityMatrix(),	const Matrix3& rot = Matrix3::identityMatrix(), 
		const Matrix3& scale = Matrix3::identityMatrix(), Transform* parent = nullptr);
	~Transform();

	std::string getSaveString();
	static Transform* createFromString(const string& string);

	unsigned short getID();
	bool isInTransformTree(Transform* other);

	void addToLocalPosition(const float& x, const float& y);
	void setLocaLPosition(const float& x, const float& y);
	void setLocaLRotation(const float& angle);
	void setLocaLScale(const float& x, const float& y);

	Transform* getRoot();
	void setParent(Transform* parent);
	void removeParent();

	unsigned int childCount();
	Transform* getChild(const int& index);

	Matrix3 getTransformation();
	Vector2 getWorldPosition();
	Vector2 getLocalScale();

	virtual void getWorldPosition(Vector2& vec1, Vector2& vec2, Vector2& vec3, Vector2& vec4);
	virtual void getCameraPerspectivePosition(Vector2& vec1, Vector2& vec2, Vector2& vec3, Vector2& vec4);

protected:

	static unsigned short idCounter;

	unsigned short id;
	Matrix3 translation;
	Matrix3 rotation;
	Matrix3 scale;
	Matrix3 transformation;

	vector<Transform*> children;

	void updateTransform();
};

