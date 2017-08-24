#pragma once

#include "..\Transform.h"

class RectTransform : public Transform {

public:

	RectTransform(const Matrix3& trans = Matrix3::identityMatrix(), const Matrix3& rot = Matrix3::identityMatrix(),
		const Matrix3& scale = Matrix3::identityMatrix(), RectTransform* parent = nullptr);

	string getSaveString();
	static RectTransform* createFromString(const string& str);

	void setParent(RectTransform* other);
	RectTransform* getChild(const int& index);

	void getCameraPerspectivePosition(Vector2& vec1, Vector2& vec2, Vector2& vec3, Vector2& vec4) override;
};

