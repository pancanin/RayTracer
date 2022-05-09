#pragma once

#include "utils.h"

class lambertian : public material {
public:
    lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        // In the lambertian approach to scatter, we calculate a random vector from the normal to the surface of the sphere.
        auto scatter_direction = rec.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        // The new ray comming out of the surface of the currently hit object.
        scattered = ray(rec.p, scatter_direction);
        // albedo is a measurement of how much light the surface reflects.
        attenuation = albedo;
        return true;
    }

public:
    color albedo;
};
