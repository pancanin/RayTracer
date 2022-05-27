#include "Ray.h"

Ray::Ray(const Point3& origin, const Vector3& direction) : origin(origin), direction(direction) {}

Point3 Ray::at(double t) const {
	return origin + (direction * t);
}