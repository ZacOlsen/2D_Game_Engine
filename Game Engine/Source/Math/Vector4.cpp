#include "Vector4.h"

Vector4::Vector4() : Vector4(0, 0, 0, 0) {}

Vector4::Vector4(const float& x, const float& y, const float& z, const float& w) : Vector3(x, y, z) {
	this->w = w;
}

Vector4::~Vector4() {}

float& Vector4::operator[](const unsigned int& index) {

	switch (index) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	}

	throw exception();
}

float Vector4::operator[](const unsigned int& index) const {

	switch (index) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	}

	throw exception();
}

Vector4 Vector4::normalized() const {
	float mag = magnitude();
	return mag != 0 ? (*this) / mag : (*this);
}

float Vector4::magnitude() const {
	return sqrtf(x * x + y * y + z * z + w * w);
}

float Vector4::sqMagnitude() const {
	return x * x + y * y + z * z + w * w;
}

void operator+=(Vector4& vec, const Vector4& other) {
	vec.x += other.x;
	vec.y += other.y;
	vec.z += other.z;
	vec.w += other.w;
}

void operator-=(Vector4& vec, const Vector4& other) {
	vec.x -= other.x;
	vec.y -= other.y;
	vec.z -= other.z;
	vec.w -= other.w;
}

Vector4 operator+(const Vector4& vec, const Vector4& other) {
	return Vector4(vec.x + other.x, vec.y + other.y, vec.z + other.z, vec.w + other.w);
}

Vector4 operator-(const Vector4& vec, const Vector4& other) {
	return Vector4(vec.x - other.x, vec.y - other.y, vec.z - other.z, vec.w - other.w);
}

float operator*(const Vector4& vec, const Vector4& other) {
	return vec.x * other.x + vec.y * other.y + vec.z * other.z + vec.w * other.w;
}

void operator*=(Vector4& vec, const float& other) {
	vec.x *= other;
	vec.y *= other;
	vec.z *= other;
	vec.w *= other;
}

void operator/=(Vector4& vec, const float& other) {
	vec.x /= other;
	vec.y /= other;
	vec.z /= other;
	vec.w /= other;
}

Vector4 operator*(const Vector4& vec, const float& other) {
	return Vector4(vec.x * other, vec.y * other, vec.z * other, vec.w * other);
}

Vector4 operator/(const Vector4& vec, const float& other) {
	return Vector4(vec.x / other, vec.y / other, vec.z / other, vec.w / other);
}

bool operator==(const Vector4& vec, const Vector4& other) {
	return vec.x == other.x && vec.y == other.y && vec.z == other.z && vec.w == other.w;
}

bool operator!=(const Vector4& vec, const Vector4& other) {
	return !(vec == other);
}

ostream& operator<<(ostream& stream, const Vector4& vec) {
	stream << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
	return stream;
}