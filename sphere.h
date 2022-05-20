#pragma once

#include "hittable.h"

class sphere : public hittable {
public:
	sphere() {}
	sphere(point3 cen, double r, shared_ptr<material> m) : center(cen), radius(r), mat(m) {}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
public:
	point3 center;
	double radius;
    shared_ptr<material> mat;
};

/**
* Analytic solution for finding if ray 'r' intersects sphere.
* 
* We start with the fact that a sphere is an implicit object and can be represented in formula.
* x^2 + y^2 + z^2 = R^2
* 
* The set of points which is defined by the equation are the set of points on the surface of sphere.
* 
* If we look at x,y,z as components of point P, we can rewrite the equation like so:
* 
* P^2 - R^2 = 0
* 
* And if we define P as O + t*D then
* 
* (O + t*D)^2 - R^2 = 0, which we can develop to:
* 
* O^2 + 2*O*t*D + (tD)^2 - R^2 = 0, we can rearrange so that it looks more like quadratic equation.
* 
* D^2*t^2 + 2*O*D*t + 0^2 - R^2 = 0, t is our x
* ax^2    + bx      + c
* 
* a = D^2, b = 2*O*D, c = 0^2 - R^2
* 
* From the quadratic equation formula we find the discriminant:
* d = b^2 - 4*a*c
* If d > 0 we got two roots, meaning that ray passed through sphere
* If d == 0 we got 1 root, ray is a tangent to sphere
* If d < 0 the ray doesn't intersect the sphere.
* 
* When the sphere's center is not at (0, 0, 0) the equation has to be adjusted.
* If C is a point at the center of sphere then
* (P - C)^2 - R^2 = 0
* 
* Which after rearranging is:
* 
*/
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().components_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.components_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = unit_vector((rec.p - center) / radius);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat;

    return true;
}