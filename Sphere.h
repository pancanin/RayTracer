#pragma once

#include <memory>

#include "Ray.h"
#include "IntersectionData.h"
#include "Material.h"
#include "Intersectable.h"

class Sphere : public Intersectable
{
public:
	Sphere(Point3 center, double radius, std::shared_ptr<Material> matPtr);

	/*
	* Based on the analytical approach in this article:
	* https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
	*/
	IntersectionData intersectWith(const Ray& ray) const override;

	Color calculateColor(const Ray& ray) const;

	std::shared_ptr<Material> getMaterial() const;
private:
	Point3 center;
	double radius;
	std::shared_ptr<Material> materialPtr;
};

