#pragma once

#include <memory>

#include "Ray.h"
#include "IntersectionData.h"
#include "Vector3.h"
#include "Material.h"

class Intersectable {
public:
	virtual IntersectionData intersectWith(const Ray& ray) const = 0;
	virtual Color calculateColor(const Ray& ray) const = 0;
	virtual std::shared_ptr<Material> getMaterial() const = 0;
};
