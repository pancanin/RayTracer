#pragma once

#include "Ray.h"

class Camera
{
public:
	Camera(Point3 lensPosition, double aspectRatio, double viewportHeight, double focalLength);

	Ray calculateOffsetRay(double x, double y) const;

	Ray getFocalRay() const;
private:
	double aspectRatio;
	double focalLength;
	double viewportHeight;
	double viewportWidth;
	Point3 lensPosition;
	Ray initialRay;

	/**
	* Based on the focal length, viewport height and width, calculate the ray from the camera to the upper left corner.
	* The center of the viewport will be at Point3(0, 0, focalLength)
	*/
	Ray calculateInitialRay();
};
