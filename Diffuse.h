#pragma once

#include "Material.h"
#include "IntersectionData.h"
#include "Ray.h"

class Diffuse : public Material
{
public:
	Diffuse(const Color& color, int attenuation);

	Color shade(const IntersectionData& intrsData) const override;

	static Ray createRandomRay(const IntersectionData& intrsData);
};
