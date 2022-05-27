#include "Vector3.h"

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
	return Vector3(this->x() * scalar, this->y() * scalar, this->z() * scalar);
}