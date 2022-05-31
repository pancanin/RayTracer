#include "Diffuse.h"

#include "Utils.h"
#include "MaterialType.h"

Diffuse::Diffuse(const Color& color, double attenuation) : Material(color, MaterialType::DIFFUSE, attenuation) {}

Color Diffuse::shade(const IntersectionData& intrsData) const {
	return color;
}

Ray Diffuse::createRandomRay(const IntersectionData& intrsData) {
	Vector3 randomRayDirection = intrsData.intersectionNormal + intrsData.intersectionRayVector + Utils::randomVectorInUnitCircle();

	return Ray(intrsData.intersectionRayVector, randomRayDirection);
}
