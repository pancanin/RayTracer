#pragma once

#include "Vector3.h"
#include "IntersectionData.h"
#include "MaterialType.h"

class Material {
public:
	Material(const Color& color, MaterialType type, double attenuation) : color(color), type(type), attenuation(attenuation) {}

	virtual Color shade(const IntersectionData& intrsData) const = 0;
	
	MaterialType getType() const { return type; }
	double getAttenuation() const { return attenuation; }
protected:
	Color color;
	MaterialType type;
private:
	double attenuation;
};
