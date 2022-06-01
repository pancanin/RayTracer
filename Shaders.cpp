#include "Shaders.h"
#include "Utils.h"

Color Shaders::shadeBasedOnPosition(const Ray& ray) {
	double r = ray.getDirection().x();
	double g = ray.getDirection().y();
	double b = 0.25;

	return Color(r, g, b);
}

Color Shaders::shadeBasedOnCenterDistance(const Ray& ray, const Ray& focalCenter) {
	Vector3 centerToRay = ray.getDirection() - focalCenter.getDirection();
	double centerToRayLength = centerToRay.calculateLength();

	return Color(centerToRayLength * 0.4, centerToRayLength * 0.1, centerToRayLength * 0.9);
}

Color Shaders::shadeBasedOnIntersectionData(const IntersectionData& intrsData) {
	if (intrsData.hasIntersection) {
		double angleRelationRayNormal = intrsData.intersectionRayVector
			.calculateNormal()
			.calculateDotProduct(intrsData.intersectionNormal);

		// to get a stronger contrast we raise the dot product of the intersection and normal to the power of 3.
		double b = angleRelationRayNormal * angleRelationRayNormal * angleRelationRayNormal;

		return Color(0, 0, b);
	}

	return Color(0.5, 0, 0);
}
