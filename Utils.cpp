#include "Utils.h"

#include <random>

double Utils::denormalise(double value, double max) {
	return max * value;
}

double Utils::random_double() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

double Utils::clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}