#include "Point3.h"

Point3::Point3(double x, double y, double z) {
	e[0] = x;
	e[1] = y;
	e[2] = z;
}

double Point3::x() const {
	return e[0];
}

double Point3::y() const {
	return e[1];
}

double Point3::z() const {
	return e[2];
}

Point3 Point3::operator+(const Vector3& vec) const {
	return Point3(this->x() + vec.x(), this->y() + vec.y(), this->z() + vec.z());
}