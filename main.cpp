#include <iostream>

#include "PPMImage.h"
#include "Camera.h"
#include "Shaders.h"
#include "IntersectionData.h"
#include "Sphere.h"
#include "GranmasButtonsMaterial.h"

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

    std::shared_ptr<Material> ballMaterial = std::make_shared<GranmasButtonsMaterial>(Color(235, 161, 52));
    std::shared_ptr<Material> planetMaterial = std::make_shared<GranmasButtonsMaterial>(Color(52, 235, 165));
    Sphere ball(Point3(0, 0, -2), 1, ballMaterial);
    Sphere planet(Point3(0, -50.5, -1), 50, planetMaterial);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            double offsetX = static_cast<double>(col) / width;
            double offsetY = static_cast<double>(row) / height;
            Ray currentRay = camera.calculateOffsetRay(offsetX, offsetY);

            Color pixelColor = planet.calculateColor(currentRay);

            img.writeColor(std::cout, pixelColor);
        }
    }
}
