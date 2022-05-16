#pragma once

#include "utils.h"

class camera {
public:
    camera(
        point3 lookfrom,
        point3 lookat,
        vec3 vertical_up,
        double vertical_field_of_view,
        double aspect_ratio,
        double aperture, // the diameter of the lens
        double focus_dist // at what distance from the lense the image looks focused.
    ) {
        auto theta = degrees_to_radians(vertical_field_of_view);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vertical_up, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lense_radius = aperture / 2;
    }

    ray get_ray(double s, double t) const {
        vec3 randomAtLens = lense_radius * random_in_unit_disk();
        vec3 offset = u * randomAtLens.x() + v * randomAtLens.y();
        
        return ray(offset + origin, lower_left_corner + s * horizontal + t * vertical - origin - offset);
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lense_radius;
};
