#pragma once

#include "Material.h"

class GranmasButtonsMaterial : public Material
{
public:
	GranmasButtonsMaterial(const Color& color);

	Color shade(const IntersectionData& intrsData) const override;
};

