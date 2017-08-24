#pragma once

#include "Vector3.h"

#define LENGTH_OF_VEC4 4

class Vector4 :	public Vector3 {

public:
	float w;

	Vector4();
	Vector4(const float& x, const float& y, const float& z, const float& w);

	float& operator[](const unsigned int& index);
	float operator[](const unsigned int& index) const;

	Vector4 normalized() const;
	float magnitude() const;
	float sqMagnitude() const;

	void friend operator+=(Vector4& vec, const Vector4& other);
	void friend operator-=(Vector4& vec, const Vector4& other);

	Vector4 friend operator+(const Vector4& vec, const Vector4& other);
	Vector4 friend operator-(const Vector4& vec, const Vector4& other);
	float friend operator*(const Vector4& vec, const Vector4& other);

	void friend operator*=(Vector4& vec, const float& other);
	void friend operator/=(Vector4& vec, const float& other);

	Vector4 friend operator*(const Vector4& vec, const float& other);
	Vector4 friend operator/(const Vector4& vec, const float& other);

	bool friend operator==(const Vector4& vec, const Vector4& other);
	bool friend operator!=(const Vector4& vec, const Vector4& other);

	friend ostream& operator<<(ostream& stream, const Vector4& vec);

};

