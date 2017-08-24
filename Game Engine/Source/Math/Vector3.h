#pragma once

#include "Vector2.h"

#define LENGTH_OF_VEC3 3

class Vector3 : public Vector2 {

public:
	float z;
	
	Vector3();
	Vector3(const float& x, const float& y, const float& z);

	float& operator[](const unsigned int& index);
	float operator[](const unsigned int& index) const;

	Vector3 normalized() const;
	float magnitude() const;
	float sqMagnitude() const;

	void friend operator+=(Vector3& vec, const Vector2& other);
	void friend operator+=(Vector3& vec, const Vector3& other);
	void friend operator-=(Vector3& vec, const Vector3& other);

	Vector3 friend operator+(const Vector3& vec, const Vector3& other);
	Vector3 friend operator-(const Vector3& vec, const Vector3& other);
	float friend operator*(const Vector3& vec, const Vector3& other);
	float friend operator*(const Vector3& vec, const Vector2& other);

	void friend operator*=(Vector3& vec, const float& other);
	void friend operator/=(Vector3& vec, const float& other);

	Vector3 friend operator*(const Vector3& vec, const float& other);
	Vector3 friend operator/(const Vector3& vec, const float& other);

	bool friend operator==(const Vector3& vec, const Vector3& other);
	bool friend operator!=(const Vector3& vec, const Vector3& other);

	friend ostream& operator<<(ostream& stream, const Vector3& vec);
};

