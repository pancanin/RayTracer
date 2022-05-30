#include "GranmasButtonsMaterial.h"

GranmasButtonsMaterial::GranmasButtonsMaterial(const Color& color) : Material(color) {}

Color GranmasButtonsMaterial::shade(const IntersectionData& intrsData) const {
	double angleRelationRayNormal = intrsData.intersectionRayVector
		.calculateNormal()
		.calculateDotProduct(intrsData.intersectionNormal);

	return color * angleRelationRayNormal * angleRelationRayNormal;
}
