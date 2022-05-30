#include "Shaders.h"
#include "Utils.h"

Color Shaders::shadeBasedOnPosition(const Ray& ray) {
	double r = Utils::denormalise(ray.getDirection().x(), 255);
	double g = Utils::denormalise(ray.getDirection().y(), 255);
	double b = Utils::denormalise(0.25, 255);

	return Color(r, g, b);
}

Color Shaders::shadeBasedOnCenterDistance(const Ray& ray, const Ray& focalCenter) {
	Vector3 centerToRay = ray.getDirection() + -focalCenter.getDirection();
	double centerToRayLength = centerToRay.calculateLength();

	return Color(centerToRayLength * 40, centerToRayLength * 10, centerToRayLength * 90);
}

Color Shaders::shadeBasedOnIntersectionData(const IntersectionData& intrsData) {
	if (intrsData.hasIntersection) {
		double angleRelationRayNormal = intrsData.intersectionRayVector
			.calculateNormal()
			.calculateDotProduct(intrsData.intersectionNormal);

		// to get a stronger contrast we raise the dot product of the intersection and normal to the power of 3.
		double b = 255 * angleRelationRayNormal * angleRelationRayNormal * angleRelationRayNormal;

		return Color(0, 0, b);
	}

	return Color(128, 0, 0);
}
