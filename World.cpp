#include "World.h"

#include "Diffuse.h"

void World::add(std::shared_ptr<Intersectable> worldObj) {
	worldObjects[idx++] = worldObj;
}

Color World::calculateColor(const Ray& ray) const {

	if (depth > maxDepth) {
		depth = 0;
		return Color(0, 0, 0);
	}

	for (int i = 0; i < idx; i++) {
		std::shared_ptr<Intersectable> current = worldObjects[i];
		IntersectionData intrsData = current.get()->intersectWith(ray);

		if (intrsData.hasIntersection) {
			Material* material = current.get()->getMaterial().get();
			MaterialType materialType = material->getType();

			if (materialType == MaterialType::DIFFUSE) {
				depth++;
				Color bounceRayColor = calculateColor(Diffuse::createRandomRay(intrsData));

				//std::cerr << bounceRayColor * current.get()->getMaterial().get()->getAttenuation() << '\n';
				Color c = current.get()->getMaterial()->shade(intrsData) +
					(bounceRayColor *
					current.get()->getMaterial().get()->getAttenuation());

				return c;
			}
			else if (materialType == MaterialType::METAL) {
				Vector3 reflectionVector = material->shade(intrsData);
				Ray reflectionRay = Ray(intrsData.intersectionRayVector, reflectionVector);

				if (reflectionVector.calculateDotProduct(intrsData.intersectionNormal) < 0) {
					return Color(0, 0, 0);
				}

				return calculateColor(reflectionRay);
			}

			return current.get()->getMaterial()->shade(intrsData);
		}
	}

	Vector3 unitDirection = ray.getDirection().calculateNormal();
	double t = 0.5 * (unitDirection.y() + 1.0);

	return Color(1.0, 1.0, 1.0) * (1.0 - t) + Color(0.5, 0.7, 1.0) * t;
}
