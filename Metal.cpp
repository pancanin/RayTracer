#include "Metal.h"

#include "MaterialType.h"

Metal::Metal(const Color& color, double attenuation) : Material(color, MaterialType::METAL, attenuation) {}

Color Metal::shade(const IntersectionData& intrsData) const {
	return intrsData.intersectionRayVector.reflect(intrsData.intersectionNormal);
}
