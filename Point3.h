#pragma once

#include "Vector3.h"

class Point3
{
public:
	Point3(double x, double y, double z);

	double x() const;
	double y() const;
	double z() const;

	Point3 operator+(const Vector3& vec) const;
private:
	double e[3];
};
