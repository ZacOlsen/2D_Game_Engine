#include "Matrix3.h"

Matrix3::Matrix3() : Matrix3 (Vector3(), Vector3(), Vector3()) {}

Matrix3::Matrix3(const Vector3& col1, const Vector3& col2, const Vector3& col3) {
	matrix[0] = col1;
	matrix[1] = col2;
	matrix[2] = col3;
}

Matrix3::~Matrix3() {}

Vector3& Matrix3::getRow(const unsigned int& index) const {
	return Vector3(matrix[0][index], matrix[1][index], matrix[2][index]);
}

Vector3& Matrix3::operator[](const unsigned int& index) {
	return matrix[index];
}

Vector3 Matrix3::operator[](const unsigned int& index) const {
	return matrix[index];
}

Matrix3 Matrix3::transpose() const {

	Matrix3 mat = Matrix3();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mat[i][j] = matrix[j][i];
		}
	}

	return mat;
}

Matrix3 Matrix3::invert() const {

	float determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] +
		matrix[1][0] * matrix[2][1] * matrix[0][2] +
		matrix[2][0] * matrix[0][1] * matrix[1][2] -
		matrix[2][0] * matrix[1][1] * matrix[0][2] -
		matrix[1][0] * matrix[0][1] * matrix[2][2] -
		matrix[0][0] * matrix[2][1] * matrix[1][2];

	Matrix3 mat = Matrix3();

	mat[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
	mat[0][1] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
	mat[0][2] = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];
	mat[1][0] = -(matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2]);
	mat[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
	mat[1][2] = -(matrix[0][0] * matrix[2][1] - matrix[2][0] * matrix[0][1]);
	mat[2][0] = matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2];
	mat[2][1] = -(matrix[0][0] * matrix[1][2] - matrix[1][0] * matrix[0][2]);
	mat[2][2] = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];

	mat = mat.transpose();

/*	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			float det = 0;

			for (int k = 0; k < 3; k++) {
				if (k == i) { continue; }
				for (int l = 0; l < 3; l++) {
					if (j == l) { continue; }
					
				}
			}

			if ((j + i) % 2 == 0) {
				mat[i][j] = de
			} else {
				mat[i][j] = -
			}
		}
	}
	*/

	return mat;
}

Matrix3 operator/(const Matrix3& mat, const float& num) {

	Matrix3 scaledMat = Matrix3();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scaledMat[i][j] = mat[i][j] / num;
		}
	}

	return scaledMat;
}

Matrix3 operator*(const Matrix3& matL, const Matrix3& matR) {
	
	Matrix3 mat = Matrix3();

	for (unsigned int i = 0; i < LENGTH_OF_VEC3; i++) {
		for (unsigned int j = 0; j < LENGTH_OF_VEC3; j++) {

			float sum = 0;
			for (unsigned int k = 0; k < LENGTH_OF_VEC3; k++) {
				sum += matL[k][i] * matR[j][k];
			}
			mat[j][i] = sum;
		}
	}

	return mat;
}

Vector2 operator*(const Matrix3& mat, const Vector2& vec) {
	return Vector2(mat.getRow(0) * vec, mat.getRow(1) *  vec);
}

ostream& operator<<(ostream& stream, const Matrix3& mat) {
	stream << mat.getRow(0) << endl;
	stream << mat.getRow(1) << endl;
	stream << mat.getRow(2);
	return stream;
}

Matrix3 Matrix3::identityMatrix() {
	return Matrix3(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));
}

Matrix3 Matrix3::translationMatrix(const float& x, const float& y) {

	Matrix3 mat = identityMatrix();
	mat[LENGTH_OF_VEC3 - 1].x = x;
	mat[LENGTH_OF_VEC3 - 1].y = y;

	return mat;
}

Matrix3 Matrix3::rotationMatrix(const float& angle) {

	float rad = angle * PI / 180.0f;

	Matrix3 mat = identityMatrix();
	mat[0].x = cosf(rad);
	mat[1].x = -sinf(rad);
	mat[0].y = -mat[1].x;
	mat[1].y = mat[0].x;

	return mat;
}

Matrix3 Matrix3::scaleMatrix(const float& x, const float& y) {
	
	Matrix3 mat = identityMatrix();
	mat[0].x = x;
	mat[1].y = y;

	return mat;
}
