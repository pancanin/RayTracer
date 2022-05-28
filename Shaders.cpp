#include "Shaders.h"
#include "Utils.h"

Color Shaders::shadeBasedOnPosition(const Ray& ray) {
	double r = Utils::denormalise(ray.getDirection().x(), 255);
	double g = Utils::denormalise(ray.getDirection().y(), 255);
	double b = Utils::denormalise(0.25, 255);

	return Color(r, g, b);
}

Color Shaders::shadeBasedOnCenterDistance(const Ray& ray, const Ray& focalCenter) {
	double crossProduct = ray.getDirection().calculateCrossProduct(focalCenter.getDirection()).calculateLength();

	std::cerr << crossProduct << '\n' << std::flush;

	return Color(0, 0, Utils::denormalise(crossProduct / 10.0, 255));
}