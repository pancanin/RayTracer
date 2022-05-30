#include <iostream>

#include "PPMImage.h"
#include "Camera.h"
#include "Shaders.h"
#include "IntersectionData.h"
#include "Sphere.h"

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

    Sphere sp1(Point3(0, 0, -2), 1);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            double offsetX = static_cast<double>(col) / width;
            double offsetY = static_cast<double>(row) / height;
            Ray currentRay = camera.calculateOffsetRay(offsetX, offsetY);

            IntersectionData intrsData = sp1.intersectWith(currentRay);

            Color pixelColor = Shaders::shadeBasedOnIntersectionData(intrsData);

            img.writeColor(std::cout, pixelColor);
        }
    }
}
