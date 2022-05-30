#include <iostream>

#include "PPMImage.h"
#include "Camera.h"
#include "Shaders.h"
#include "IntersectionData.h"
#include "Sphere.h"
#include "GranmasButtonsMaterial.h"
#include "World.h"
#include "Utils.h"

int main()
{
    const unsigned short width = 256;
    const unsigned short maxColor = 255;
    const double aspectRatio = 16.0 / 9;
    const unsigned short height = width / aspectRatio;
    const double viewportHeight = 2.0;
    const double focalLength = 1.0;

    PPMImage img(width, height, maxColor);
    img.writePPMHeaders(std::cout);

    Point3 lensPosition(0, 0, 0);
    Camera camera(lensPosition, aspectRatio, viewportHeight, focalLength);
    const int numberOfSamplesPerPixel = 100;

    World world;

    std::shared_ptr<Material> ballMaterial = std::make_shared<GranmasButtonsMaterial>(Color(235, 161, 52));
    std::shared_ptr<Material> planetMaterial = std::make_shared<GranmasButtonsMaterial>(Color(52, 235, 165));
    Sphere ball(Point3(0, 0, -2), 1, ballMaterial);
    Sphere planet(Point3(0, -50.5, -1), 50, planetMaterial);

    world.add(std::make_shared<Sphere>(Point3(0, -50.5, -1), 50, planetMaterial));
    world.add(std::make_shared<Sphere>(Point3(0, 0, -2), 1, ballMaterial));

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Color pixelColor = Color(0, 0, 0);

            for (int sampleN = 0; sampleN < numberOfSamplesPerPixel; sampleN++) {
                double offsetX = static_cast<double>(col + Utils::random_double()) / width;
                double offsetY = static_cast<double>(row + Utils::random_double()) / height;
                Ray currentRay = camera.calculateOffsetRay(offsetX, offsetY);

                pixelColor = pixelColor + world.calculateColor(currentRay);
            }

            img.writeColor(std::cout, pixelColor * (1.0/numberOfSamplesPerPixel));
        }
    }
}
