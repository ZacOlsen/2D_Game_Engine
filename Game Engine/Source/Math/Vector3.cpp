#include "Vector3.h"

Vector3::Vector3() : Vector3(0, 0, 0) {}

Vector3::Vector3(const float& x, const float& y, const float& z) : Vector2(x, y) {
	this->z = z;
}

Vector3::~Vector3() {}

float& Vector3::operator[](const unsigned int& index) {
	
	switch (index) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}

	throw exception();
}

float Vector3::operator[](const unsigned int& index) const {
	
	switch (index) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}

	throw exception();
}

Vector3 Vector3::normalized() const {
	float mag = magnitude();
	return mag != 0 ? (*this) / mag : (*this);
}

float Vector3::magnitude() const {
	return sqrtf(x * x + y * y + z * z);
}

float Vector3::sqMagnitude() const {
	return x * x + y * y + z * z;
}

void operator+=(Vector3& vec, const Vector2& other) {
	vec.x += other.x;
	vec.y += other.y;
}

void operator+=(Vector3& vec, const Vector3& other) {
	vec.x += other.x;
	vec.y += other.y;
	vec.z += other.z;
}

void operator-=(Vector3& vec, const Vector3& other) {
	vec.x -= other.x;
	vec.y -= other.y;
	vec.z -= other.z;
}

Vector3 operator+(const Vector3& vec, const Vector3& other) {
	return Vector3(vec.x + other.x, vec.y + other.y, vec.z + other.z);
}

Vector3 operator-(const Vector3& vec, const Vector3& other) {
	return Vector3(vec.x - other.x, vec.y - other.y, vec.z - other.z);
}

float operator*(const Vector3& vec, const Vector3& other) {
	return vec.x * other.x + vec.y * other.y + vec.z * other.z;
}

float operator*(const Vector3& vec, const Vector2& other) {
	return vec.x * other.x + vec.y * other.y + vec.z;
}

void operator*=(Vector3& vec, const float& other) {
	vec.x *= other;
	vec.y *= other;
	vec.z *= other;
}

void operator/=(Vector3& vec, const float& other) {
	vec.x /= other;
	vec.y /= other;
	vec.z /= other;
}

Vector3 operator*(const Vector3& vec, const float& other) {
	return Vector3(vec.x * other, vec.y * other, vec.z * other);
}

Vector3 operator/(const Vector3& vec, const float& other) {
	return Vector3(vec.x / other, vec.y / other, vec.z / other);
}

bool operator==(const Vector3& vec, const Vector3& other) {
	return vec.x == other.x && vec.y == other.y && vec.z == other.z;
}

bool operator!=(const Vector3& vec, const Vector3& other) {
	return !(vec == other);
}

ostream& operator<<(ostream& stream, const Vector3& vec) {
	stream << vec.x << ", " << vec.y << ", " << vec.z;
	return stream;
}
