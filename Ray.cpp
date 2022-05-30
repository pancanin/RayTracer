#include "Ray.h"

Ray::Ray(const Point3& origin, const Vector3& direction) : origin(origin), direction(direction) {}

Point3 Ray::at(double t) const {
	return origin + (direction * t);
}

const Vector3& Ray::getDirection() const {
	return direction;
}

const Point3& Ray::getOrigin() const {
	return origin;
}

std::ostream& operator<<(std::ostream& os, const Ray& ray) {
	return os << "Ray x direction: " << ray.getDirection().x() << "; Ray y direction: " <<
		ray.getDirection().y() << "; Ray z direction: " << ray.getDirection().z();
}