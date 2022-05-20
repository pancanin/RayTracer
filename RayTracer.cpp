// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "utils.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color ray_color(const ray& r, const hittable& world, int depth) {
    if (depth <= 0) {
        return color(0, 0, 0);
    }
    hit_record hit_data;
    // For min t we are setting a value a bit bigger than 0 to avoid Shadow Acne.
    bool isHit = world.hit(r, 0.001, infinity, hit_data);
    
    if (isHit) {
        ray scattered;
        color attenuation;

        // If we have hit something then we cast another ray in a direction:
        // For diffuse materials the direction is random.
        // For metal materials the reflection is a mirrored one.
        // `attenuation` is a color which decreases the light from each ray, because as the distance increases light in real world get scattered and becomes less focused.
        if (hit_data.mat_ptr->scatter(r, hit_data, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0);
    }

    // Get a normalized vector of the direction the ray is pointing to.
    vec3 unit_direction = unit_vector(r.direction());

    // Calculate a step for the linear interpolation based on y.
    // The constants around y just make sure the step is finer for a softer gradient.
    auto t = 0.5 * (unit_direction.y() + 1.0);

    // We linearly interpolate between white and bluish color.
    return lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), t);
}

int main()
{
    const double aspect_ratio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspect_ratio);
    const int numberOfSamples = 100;

    // World

    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2));

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

    point3 lookfrom(0, 0, -2);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = (lookfrom - lookat).length();
    auto aperture = 1.0;

    camera cam(lookfrom, lookat, vup, 90, aspect_ratio, aperture, dist_to_focus);

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
                pixelColor += ray_color(r, world, 50);
            }

            write_color(std::cout, pixelColor, numberOfSamples);
        }
    }

    std::cerr << "Done!" << std::flush;
}
