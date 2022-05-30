#include "Sphere.h"

Sphere::Sphere(Point3 center, double radius, std::shared_ptr<Material> matPtr) :
	center(center),
	radius(radius),
	materialPtr(matPtr) {}

IntersectionData Sphere::intersectWith(const Ray& ray) const {
	IntersectionData data{ false, Vector3(0, 0, 0), Vector3(0, 0, 0) };

	// Note: we are considering the cases when center of sphere is not at origin 0,0,0 by traslating the ray with -C.
	// // Note: Equation of point P is = O + tD (origin plus direction multiplied by scalar)
	// (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = R^2
	// (P - C)^2 - R^2 = 0
	// (O + Dt - C)^2 - R^2 = 0
	// ... a few expansions ...
	// We find the coefficients of a quadratic equation.
	// a = D^2 (we assume D vector might not be normalised.
	// b = 2*D*(O - C)
	// c = (O - C)^2 - R^2

	Vector3 offsetRayOrigin = ray.getOrigin() + -center;
	double offsetRayOriginSquared = offsetRayOrigin.calculateDotProduct(offsetRayOrigin);

	double a = ray.getDirection().calculateDotProduct(ray.getDirection());
	double b = ray.getDirection().calculateDotProduct(offsetRayOrigin) * 2;
	double c = offsetRayOriginSquared - radius * radius;

	double det = b * b - 4 * a * c;

	if (det > 0) {
		// two roots -> two intersection points
		double t0 = (-b + sqrt(det)) / 2 * a;
		double t1 = (-b - sqrt(det)) / 2 * a;

		if (t0 < 0) {
			return data;
		}

		// calculate frontal intersection vector
		Vector3 intersectionVector = ray.at(t0);
		Vector3 intersectionNormal = (intersectionVector + -center).calculateNormal();

		data.hasIntersection = true;
		data.intersectionRayVector = intersectionVector;
		data.intersectionNormal = intersectionNormal;
	}
	else if (det == 0) {
		// one root -> one intersection point, ray is a tangent to the sphere.
		double t = -(b / 2 * a);

		// we will ignore these for now as they are just slightly touching the sphere.
	}
	else {
		// Ray does not intersect sphere
	}

	return data;
}

Color Sphere::calculateColor(const Ray& ray) const {
	IntersectionData d = this->intersectWith(ray);

	if (d.hasIntersection) {
		return materialPtr.get()->shade(d);
	}
	
	return Color(255, 255, 255);
}