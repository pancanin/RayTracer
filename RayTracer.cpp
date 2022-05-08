// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "utils.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

// Linear interpolation
vec3 lerp(const vec3& start, const vec3& end, double t) {
    return (1.0 - t) * start + t * end;
}

color ray_color(const ray& r, const hittable& world) {
    hit_record hit_data;
    bool isHit = world.hit(r, 0, infinity, hit_data);
    
    if (isHit) {
        // We will shade using the normal of the sphere at point of intersection. The normal will be of unit vector length.
        // We get the normal vector by subtracting the point of intersection
        return 0.5 * (hit_data.normal + color(1, 1, 1));
    }

    // Get a normalized vector of the direction the ray is pointing to.
    vec3 unit_direction = unitVector(r.direction());

    // Calculate a step for the linear interpolation based on y.
    // The constants around y just make sure the step is finer for a softer gradient.
    auto t = 0.5 * (unit_direction.y() + 1.0);

    // We linearly interpolate between white and bluish color.
    return lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), t);
}

int main()
{
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int numberOfSamples = 100;

    camera cam;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
   


    // Render
    std::cout << "P3" << std::endl << imageWidth << " " << imageHeight << std::endl << "255" << std::endl;

    for (int j = imageHeight - 1; j >= 0; --j) {
        //std::cerr << "Scanlines remaining: " << j << ' \n' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            color pixelColor(0, 0, 0);
            for (int sample = 0; sample < numberOfSamples; sample++) {

                // Normalise values of u and v.
                double u = (double(i) + random_double()) / (imageWidth - 1);
                double v = (double(j) + random_double()) / (imageHeight - 1);

                // Calculate a direction vector for the ray.
                // By multiplying the horizontal and vertical vectors with the normalized u, v values
                // we find the value of the current component (x, y).
                // For example: in start of the loop we got:
                // j = 254, i = 0, imageHeight = 255, imageWidth = 400
                // v = j / (imageHeight - 1), v = 254 / (255 - 1), v = 1
                // u = i / (imageWidth - 1), u = 0

                // v = 1, u = 0
                // horizontal = (4, 0, 0), vertical = (0, 2, 0)
                // horizontal * u = (4, 0, 0) * 0 = (0, 0, 0)
                // vertical * v = (0, 2, 0) * 1 = (0, 2, 0)

                // For our viewport sizes, we calculated that the lower left corner is pointed by a vector
                // from origin to (-1.77, -1, -1).
                // So the direction of the first ray that we will cast will be:
                // dir = (-1.77, -1, -1) + (0, 0, 0) + (0, 2, 0) - (0, 0, 0)
                // dir = (-1.77, 1, -1)

                // On the second iteration i = 1, 'u' will become > 0 and we will get a direction slightly to the right.

                ray r = cam.get_ray(u, v);
                pixelColor += ray_color(r, world);
            }

            write_color(std::cout, pixelColor, numberOfSamples);
        }
    }

    std::cerr << "Done!" << std::flush;
}
