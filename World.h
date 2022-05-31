#pragma once

#include <memory>

#include "Intersectable.h"

class World
{
public:
	void add(std::shared_ptr<Intersectable> worldObj);
	Color calculateColor(const Ray& ray) const;
private:
	std::shared_ptr<Intersectable> worldObjects[100];
	int idx = 0;
	mutable int depth = 0;
	int maxDepth = 100;
};
