#pragma once

#include <vector>
#include "Component.h"

class Transform : public Component {

public:

	Transform(const Matrix3& trans = Matrix3::identityMatrix(),	const Matrix3& rot = Matrix3::identityMatrix(), 
		const Matrix3& scale = Matrix3::identityMatrix(), Transform* parent = nullptr);

	std::string getSaveString();
	static Transform* createFromString(const string& string);

	const unsigned short getID() const;
	const bool isInTransformTree(const Transform* other) const;

	void addToLocalPosition(const float& x, const float& y);
	void setLocaLPosition(const float& x, const float& y);
	void setLocaLRotation(const float& angle);
	void setLocaLScale(const float& x, const float& y);

	const Transform* getRoot() const;
	void setParent(Transform* parent);
	const Transform* getParent() const;
	void removeParent();

	const unsigned int childCount() const;
	const Transform* getChild(const int& index) const;

	const Matrix3 getTransformation() const;
	const Vector2 getWorldPosition() const;
	const Vector2 getLocalScale() const;

	virtual void getWorldPosition(Vector2& vec1, Vector2& vec2, Vector2& vec3, Vector2& vec4) const;
	virtual void getCameraPerspectivePosition(Vector2& vec1, Vector2& vec2, Vector2& vec3, Vector2& vec4) const;

protected:

	Transform* parent = nullptr;
	unsigned short id;
	static unsigned short idCounter;

	Matrix3 translation;
	Matrix3 rotation;
	Matrix3 scale;
	Matrix3 transformation;

	vector<Transform*> children;

	void updateTransform();
};

