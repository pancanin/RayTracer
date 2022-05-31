#include "Utils.h"

#include <random>

#include "Vector3.h"

double Utils::denormalise(double value, double max) {
	return max * value;
}

double Utils::randomDouble() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

double Utils::randomDouble(double min, double max) {
	return min + (max - min) * randomDouble();
}

double Utils::clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

Vector3 Utils::randomVectorInUnitCircle() {
	while (true) {
		Vector3 randomVec = Vector3::randomVector(-1, 1);
		
		if (randomVec.calculateLength() >= 1) {
			continue;
		}

		return randomVec;
	}
}

Color Utils::denormalise(const Color& color, double maxValue) {
	double r = maxValue * Utils::clamp(color.x(), 0, 1);
	double g = maxValue * Utils::clamp(color.y(), 0, 1);
	double b = maxValue * Utils::clamp(color.z(), 0, 1);

	return Color(r, g, b);
}