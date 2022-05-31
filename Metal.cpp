#include "Metal.h"

#include "MaterialType.h"

Metal::Metal(const Color& color, double attenuation) : Material(color, MaterialType::METAL, attenuation) {}

Color Metal::shade(const IntersectionData& intrsData) const {
	Vector3 intersectionVectorExtended = intrsData.intersectionRayVector * 2;
	Vector3 projectionOnNormal = intersectionVectorExtended.calculateProjection(intrsData.intersectionNormal);

	return -projectionOnNormal * 2 + intersectionVectorExtended;
}
