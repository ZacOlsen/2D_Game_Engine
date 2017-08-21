#pragma once

#include <iostream>

#define LENGTH_OF_VEC2 2

using namespace std;

class Vector2 {

public:
	float x;
	float y;

	Vector2();
	Vector2(const float& x, const float& y);
	~Vector2();

	float& operator[](const unsigned int& index);
	float operator[](const unsigned int& index) const;

	Vector2 normalized() const;
	float magnitude() const;
	float sqMagnitude() const;

	void friend operator+=(Vector2& vec, const Vector2& other);
	void friend operator-=(Vector2& vec, const Vector2& other);
	
	Vector2 friend operator+(const Vector2& vec, const Vector2& other);
	Vector2 friend operator-(const Vector2& vec, const Vector2& other);
	float friend operator*(const Vector2& vec, const Vector2& other);
	
	void friend operator*=(Vector2& vec, const float& other);
	void friend operator/=(Vector2& vec, const float& other);

	Vector2 friend operator*(const Vector2& vec, const float& other);
	Vector2 friend operator/(const Vector2& vec, const float& other);

	bool friend operator==(const Vector2& vec, const Vector2& other);
	bool friend operator!=(const Vector2& vec, const Vector2& other);

	friend ostream& operator<<(ostream& stream, const Vector2& vec);
};

