#pragma once

#include "Vector3.h"
#include "IntersectionData.h"

class Material {
public:
	Material(const Color& color) : color(color) {}

	virtual Color shade(const IntersectionData& intrsData) const = 0;
protected:
	Color color;
};
