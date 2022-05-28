#include "Vector3.h"

#include <math.h>

Vector3::Vector3(double x, double y, double z) {
	e[0] = x;
	e[1] = y;
	e[2] = z;
}

double Vector3::x() const {
	return e[0];
}
double Vector3::y() const {
	return e[1];
}
double Vector3::z() const {
	return e[2];
}

Vector3 Vector3::operator*(double scalar) const {
	return Vector3(x() * scalar, y() * scalar, z() * scalar);
}

Vector3 Vector3::operator+(const Vector3& other) const {
	return Vector3(x() + other.x(), y() + other.y(), z() + other.z());
}

double Vector3::calculateDotProduct(const Vector3& other) const {
	return x() * other.x() +
		y() * other.y() +
		z() * other.z();
}

Vector3 Vector3::calculateCrossProduct(const Vector3& other) const {
	return Vector3(
		y() * other.z() - z() * other.y(),
		x() * other.z() - z() * other.x(),
		x() * other.y() - y() * other.x()
	);
}

double Vector3::calculateLength() const {
	return sqrt(x() * x() + y() * y() + z() * z());
}
