#include "GranmasButtonsMaterial.h"

#include "Utils.h"

GranmasButtonsMaterial::GranmasButtonsMaterial(const Color& color) : Material(color, MaterialType::DEFAULT, 1) {}

Color GranmasButtonsMaterial::shade(const IntersectionData& intrsData) const {
	double angleRelationRayNormal = intrsData.intersectionRayVector
		.calculateNormal()
		.calculateDotProduct(intrsData.intersectionNormal);
	Color colorf = color * angleRelationRayNormal * angleRelationRayNormal;
	const double minColor = 128;
	const double maxColor = 256;

	return Color(
		Utils::clamp(colorf.x(), minColor, maxColor),
		Utils::clamp(colorf.y(), minColor, maxColor),
		Utils::clamp(colorf.z(), minColor, maxColor)
	);
}
