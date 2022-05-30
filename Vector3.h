#pragma once

class Vector3
{
public:
	Vector3(double x, double y, double z);

	double x() const;
	double y() const;
	double z() const;

	Vector3 operator*(double scalar) const;
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-() const;

	double calculateDotProduct(const Vector3& other) const;
	Vector3 calculateCrossProduct(const Vector3& other) const;
	double calculateLength() const;
	Vector3 calculateNormal() const;
private:
	double e[3];
};

using Point3 = Vector3;
using Color = Vector3;
