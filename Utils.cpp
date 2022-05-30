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

Vector3 Utils::randomVectorUnitCircle() {
	while (true) {
		Vector3 randomVec = Vector3::randomVector(-1, 1);
		
		if (randomVec.calculateLength() >= 1) {
			continue;
		}

		return randomVec;
	}
}