#include "World.h"

#include "Diffuse.h"

void World::add(std::shared_ptr<Intersectable> worldObj) {
	worldObjects[idx++] = worldObj;
}

Color World::calculateColor(const Ray& ray) const {
	Color clr(0, 0, 0);

	if (depth > maxDepth) {
		depth = 0;
		return clr;
	}

	depth++;

	for (int i = 0; i < idx; i++) {
		std::shared_ptr<Intersectable> current = worldObjects[i];
		IntersectionData intrsData = current.get()->intersectWith(ray);

		if (intrsData.hasIntersection) {
			if (current.get()->getMaterial().get()->getType() == MaterialType::DIFFUSE) {
				clr = calculateColor(Diffuse::createRandomRay(intrsData)) * current.get()->getMaterial().get()->getAttenuation();
			}
			else {
				clr = current.get()->calculateColor(ray);
			}
		}
	}

	return clr;
}
