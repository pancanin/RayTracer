#include "GranmasButtonsMaterial.h"

GranmasButtonsMaterial::GranmasButtonsMaterial(const Color& color) : Material(color) {}

Color GranmasButtonsMaterial::shade(const IntersectionData& intrsData) const {
	double angleRelationRayNormal = intrsData.intersectionRayVector
		.calculateNormal()
		.calculateDotProduct(intrsData.intersectionNormal);
	Color colorf = color * angleRelationRayNormal * angleRelationRayNormal;

	return Color(
		static_cast<int>(colorf.x()),
		static_cast<int>(colorf.y()),
		static_cast<int>(colorf.z())
	);
}
