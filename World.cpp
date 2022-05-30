#include "World.h"

void World::add(std::shared_ptr<Intersectable> worldObj) {
	worldObjects[idx++] = worldObj;
}

Color World::calculateColor(const Ray& ray) const {
	Color clr(100, 100, 100);

	for (int i = 0; i < idx; i++) {
		std::shared_ptr<Intersectable> current = worldObjects[i];
		IntersectionData intrsData = current.get()->intersectWith(ray);

		if (intrsData.hasIntersection) {
			clr = current.get()->calculateColor(ray);
		}
	}

	return clr;
}
