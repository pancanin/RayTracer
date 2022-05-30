#pragma once

#include "Color.h"
#include "Ray.h"
#include "IntersectionData.h"

namespace Shaders
{
	/*
	* Based on the x and y position of the ray, return a color.
	* This is silly shader, but it just had to verify that the whole thing works.
	*/
	Color shadeBasedOnPosition(const Ray& ray);

	/*
	* This shader should shade based on the distance from the center.
	* To find the distance, subtract the focal center ray with the current ray and find the length of that vector.
	*/
	Color shadeBasedOnCenterDistance(const Ray& ray, const Ray& focalCenter);

	Color shadeBasedOnIntersectionData(const IntersectionData& intrsData);
};
