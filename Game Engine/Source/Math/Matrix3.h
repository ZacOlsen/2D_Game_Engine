#pragma once

#include <math.h>
#include "Vector4.h"

#define PI 3.1415926f

class Matrix3 {

public:

	//column major
	Vector3 matrix[LENGTH_OF_VEC3];

	Matrix3();
	Matrix3(const Vector3& col1, const Vector3& col2, const Vector3& col3);

	Vector3& getRow(const unsigned int& index) const;
	Vector3& operator[](const unsigned int& index);
	Vector3 operator[](const unsigned int& index) const;

	Matrix3 transpose() const;
	Matrix3 invert() const;

	Matrix3 friend operator/(const Matrix3& mat, const float& num);
	Matrix3 friend operator*(const Matrix3& matL, const Matrix3& matR);
	Vector2 friend operator*(const Matrix3& mat, const Vector2& vec);

	friend ostream& operator<<(ostream& stream, const Matrix3& mat);

	static Matrix3 identityMatrix();
	static Matrix3 translationMatrix(const float& x, const float& y);
	static Matrix3 rotationMatrix(const float& angle);
	static Matrix3 scaleMatrix(const float& x, const float& y);

	~Matrix3();
};

