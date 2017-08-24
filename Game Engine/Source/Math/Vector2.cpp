#include "Vector2.h"

Vector2::Vector2() : Vector2(0, 0) {}

Vector2::Vector2(const float& x, const float& y) {
	this->x = x;
	this->y = y;
}

float& Vector2::operator[](const unsigned int& index) {

	switch (index) {
	case 0:
		return x;
	case 1:
		return y;
	}

	throw exception();
}

float Vector2::operator[](const unsigned int& index) const {

	switch (index) {
	case 0:
		return x;
	case 1:
		return y;
	}

	throw exception();
}

Vector2 Vector2::normalized() const {
	float mag = magnitude();
	return mag != 0 ? (*this) / mag : (*this);
}

float Vector2::magnitude() const {
	return sqrtf(x * x + y * y);
}

float Vector2::sqMagnitude() const {
	return x * x + y * y;
}

void operator+=(Vector2& vec, const Vector2& other) {
	vec.x += other.x;
	vec.y += other.y;
}

void operator-=(Vector2& vec, const Vector2& other) {
	vec.x -= other.x;
	vec.y -= other.y;
}

Vector2 operator+(const Vector2& vec, const Vector2& other) {
	return Vector2(vec.x + other.x, vec.y + other.y);
}

Vector2 operator-(const Vector2& vec, const Vector2& other) {
	return Vector2(vec.x - other.x, vec.y - other.y);
}

float operator*(const Vector2& vec, const Vector2& other) {
	return vec.x * other.x + vec.y * other.y;
}

void operator*=(Vector2& vec, const float& other) {
	vec.x *= other;
	vec.y *= other;
}

void operator/=(Vector2& vec, const float& other) {
	vec.x /= other;
	vec.y /= other;
}

Vector2 operator*(const Vector2& vec, const float& other) {
	return Vector2(vec.x * other, vec.y * other);
}

Vector2 operator/(const Vector2& vec, const float& other) {
	return Vector2(vec.x / other, vec.y / other);
}

bool operator==(const Vector2& vec, const Vector2& other) {
	return vec.x == other.x && vec.y == other.y;
}

bool operator!=(const Vector2& vec, const Vector2& other) {
	return !(vec == other);
}

ostream& operator<<(ostream& stream, const Vector2& vec) {
	stream << vec.x << ", " << vec.y;
	return stream;
}