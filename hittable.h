#pragma once

#include "utils.h"

struct hit_record {
	point3 p;
	vec3 normal;
	double t;
	bool front_face;
	shared_ptr<material> mat_ptr;

	// Based on the ray and the normal pointing away from the center of the object we can calculate 
	// if it should be a front facing normal or back facing.
	// If the ray is coming from inside the object, like if we have a glass ball, we would like to point the normal inwards,
	// which can be used for shading a refraction inside the ball.
	inline void set_face_normal(const ray& r, const vec3& outward_normal) {

		// The dot product will tell us whether the ray and outward normal point at the same direction.
		// If they do, then the dot product will return a positive number and it would mean that it comes from inside the object.
		front_face = dot(r.direction(), outward_normal) < 0.0;

		// If the hit is back facing, then we set the normal to point inwards.
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
