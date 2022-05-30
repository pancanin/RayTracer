#pragma once

#include "Ray.h"
#include "IntersectionData.h"

class Sphere
{
public:
	Sphere(Point3 center, double radius);

	/*
	* Based on the analytical approach in this article:
	* https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
	*/
	IntersectionData intersectWith(const Ray& ray);
private:
	Point3 center;
	double radius;
};

