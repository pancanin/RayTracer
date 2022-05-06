// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "vec3.h"
#include "ray.h"

// Linear interpolation
vec3 lerp(const vec3& start, const vec3& end, double t) {
    return (1.0 - t) * start + t * end;
}

color ray_color(const ray& r) {
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

    // Camera
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * aspectRatio;
    double focalLenght = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewportWidth, 0, 0);
    auto vertical = vec3(0, viewportHeight, 0);

    // see image in readme about calculating lower left point.
    auto lowerLeftCorner = origin / 2 - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLenght);

    std::cerr << "Lower left corner calculation: \n" <<
        "- origin is: " << origin << '\n' <<
        "- horizontal is: " << (horizontal / 2) << '\n' <<
        "- vertical is: " << (vertical / 2) << '\n' <<
        "- focal length vec is: " << vec3(0, 0, focalLenght) << '\n' <<
        "Lower left corner is " << lowerLeftCorner << '\n' << std::flush;

    std::cerr << lowerLeftCorner << '\n' << std::flush;
    // Render
    std::cout << "P3" << std::endl << imageWidth << " " << imageHeight << std::endl << "255" << std::endl;

    for (int j = imageHeight - 1; j >= 0; --j) {
        //std::cerr << "Scanlines remaining: " << j << ' \n' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {

            // Normalise values of u and v.
            double u = double(i) / (imageWidth - 1);
            double v = double(j) / (imageHeight - 1);
            
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
            vec3 direction(lowerLeftCorner + u * horizontal + v * vertical - origin);
            //std::cerr << direct << std::endl;
            ray r(origin, direction);
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
