#pragma once

#include "Material.h"

class Metal : public Material
{
public:
	Metal(const Color& color, double attenuation);

	Color shade(const IntersectionData& intrsData) const;
};
