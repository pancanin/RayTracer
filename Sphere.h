#pragma once

#include <memory>

#include "Ray.h"
#include "IntersectionData.h"
#include "Material.h"

class Sphere
{
public:
	Sphere(Point3 center, double radius, std::shared_ptr<Material> matPtr);

	/*
	* Based on the analytical approach in this article:
	* https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
	*/
	IntersectionData intersectWith(const Ray& ray) const;

	Color calculateColor(const Ray& ray) const;
private:
	Point3 center;
	double radius;
	std::shared_ptr<Material> materialPtr;
};

