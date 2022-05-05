// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "vec3.h"
#include "ray.h"

color ray_color(const ray& r) {
    vec3 unit_direction = unitVector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    // Camera
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * aspectRatio;
    double focalLenght = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewportWidth, 0, 0);
    auto vertical = vec3(0, viewportHeight, 0);
    auto lowerLeftCorner = origin / 2 - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLenght);
    // Render
    std::cout << "P3" << std::endl << imageWidth << " " << imageHeight << std::endl << "255" << std::endl;

    for (int j = imageHeight - 1; j >= 0; --j) {
        //std::cerr << "Scanlines remaining: " << j << ' \n' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            double u = double(i) / (imageWidth - 1);
            double v = double(j) / (imageHeight - 1);
            
            vec3 direct(lowerLeftCorner + u * horizontal + v * vertical - origin);
            std::cerr << direct << std::endl;
            ray r(origin, direct);
            color pixelColor = ray_color(r);

            write_color(std::cout, pixelColor);
        }
    }

    std::cerr << "Done!" << std::flush;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
