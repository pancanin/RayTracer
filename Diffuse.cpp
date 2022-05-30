#include "Diffuse.h"

#include "Utils.h"
#include "MaterialType.h"

Diffuse::Diffuse(const Color& color, int attenuation) : Material(color, MaterialType::DIFFUSE, attenuation) {}

Color Diffuse::shade(const IntersectionData& intrsData) const {
	return color;
}

Ray Diffuse::createRandomRay(const IntersectionData& intrsData) {
	Vector3 randomVec = Utils::randomVectorUnitCircle();
	Vector3 direction = randomVec + -intrsData.intersectionRayVector;

	return Ray(intrsData.intersectionRayVector, direction);
}
