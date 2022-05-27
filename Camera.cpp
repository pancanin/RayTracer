#include "Camera.h"

Camera::Camera(double aspectRatio, double viewportHeight, double focalLength) :
	aspectRatio(aspectRatio),
	focalLength(focalLength),
	viewportHeight(viewportHeight),
	viewportWidth(viewportHeight* aspectRatio),
	initialRay(calculateInitialRay()) {}

Ray Camera::calculateInitialRay() {

}