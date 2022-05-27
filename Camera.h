#pragma once

#include "Ray.h"

class Camera
{
	Camera(double aspectRatio, double viewportHeight, double focalLength);
private:
	double aspectRatio;
	double focalLength;
	double viewportHeight;
	double viewportWidth;
	Ray initialRay;

	/// <summary>
	/// Based on the focal length, viewport height and width, calculate the ray from the camera to the upper left corner.
	/// The center of the viewport will be at Point3(0, 0, focalLength)
	/// </summary>
	/// <returns></returns>
	Ray calculateInitialRay();
};

