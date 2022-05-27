#pragma once
class Vector3
{
public:
	Vector3(double x, double y, double z);

	double x() const;
	double y() const;
	double z() const;

	Vector3 operator*(double scalar) const;
private:
	double e[3];
};

