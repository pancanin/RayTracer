#pragma once

#include "Vector3.h"

namespace Utils
{
	double denormalise(double value, double max);
	double randomDouble();
	double randomDouble(double min, double max);
	double clamp(double x, double min, double max);
	Vector3 randomVectorInUnitCircle();
	Color denormalise(const Color& color, double maxValue);
};

