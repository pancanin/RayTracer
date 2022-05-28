#include "Camera.h"

Camera::Camera(Point3 lensPosition, double aspectRatio, double viewportHeight, double focalLength) :
	lensPosition(lensPosition),
	aspectRatio(aspectRatio),
	focalLength(focalLength),
	viewportHeight(viewportHeight),
	viewportWidth(viewportHeight* aspectRatio),
	initialRay(calculateInitialRay()) {}

Ray Camera::calculateInitialRay() {
	Vector3 upperLeftCornerPosition = Vector3(-(viewportWidth / 2.0), viewportHeight / 2.0, -focalLength);

	return Ray(lensPosition, upperLeftCornerPosition);
}

Ray Camera::calculateOffsetRay(double x, double y) const {
	Ray offsetRay(lensPosition, initialRay.getDirection() + Vector3(x * viewportWidth, -y * viewportHeight, 0));

	return offsetRay;
}
