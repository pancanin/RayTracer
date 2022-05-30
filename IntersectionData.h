#pragma once

#include "Vector3.h"

struct IntersectionData {
	bool hasIntersection;
	Vector3 intersectionRayVector;
	Vector3 intersectionNormal;
};
