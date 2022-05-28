#pragma once

#include <iostream>

#include "Point3.h"
#include "Vector3.h"

class Ray
{
public:
	Ray(const Point3& origin, const Vector3& direction);
	
	/// <summary>
	/// Calculates a point on the trajectory of the ray based on a constant factor.
	/// The origin point in the calculation acts as a translation.
	/// </summary>
	/// <param name="t">The amount we scale the direction vector.</param>
	/// <returns>Returns a point at the tip of the direction vector scaled by 't'.</returns>
	Point3 at(double t) const;

	const Vector3& getDirection() const;

	friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
private:
	Point3 origin;
	Vector3 direction;
};

