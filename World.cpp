#include "World.h"

#include "Diffuse.h"

void World::add(std::shared_ptr<Intersectable> worldObj) {
	worldObjects[idx++] = worldObj;
}

Color World::calculateColor(const Ray& ray) const {
	for (int i = 0; i < idx; i++) {
		std::shared_ptr<Intersectable> current = worldObjects[i];
		IntersectionData intrsData = current.get()->intersectWith(ray);

		if (intrsData.hasIntersection) {
			return current.get()->calculateColor(ray);
		}
	}

	Vector3 unitDirection = ray.getDirection().calculateNormal();
	double t = 0.5 * (unitDirection.y() + 1.0);

	return Color(1.0, 1.0, 1.0) * (1.0 - t) + Color(0.5, 0.7, 1.0) * t;
}
