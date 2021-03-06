#include "GranmasButtonsMaterial.h"

#include "Utils.h"

GranmasButtonsMaterial::GranmasButtonsMaterial(const Color& color) : Material(color, MaterialType::DEFAULT, 1.0) {}

Color GranmasButtonsMaterial::shade(const IntersectionData& intrsData) const {
	double angleRelationRayNormal = intrsData.intersectionRayVector
		.calculateNormal()
		.calculateDotProduct(intrsData.intersectionNormal);
	Color colorf = color * angleRelationRayNormal * angleRelationRayNormal;
	const double minColor = 0.0;
	const double maxColor = 1.0;

	return Color(
		Utils::clamp(colorf.x(), minColor, maxColor),
		Utils::clamp(colorf.y(), minColor, maxColor),
		Utils::clamp(colorf.z(), minColor, maxColor)
	);
}
