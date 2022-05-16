#pragma once

#include "utils.h"

class metal : public material {
public:
    metal(const color& a) : albedo(a) {}

    /*
    * Based on the hit ray and the material's reflection, scatter a new ray.
    * This new ray may hit another object and the color of that hit object will dye the reflecting object a bit.
    */
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    // albedo measures the reflective property of a material.
    color albedo;
};
