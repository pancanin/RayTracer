#include <iostream>

#include "PPMImage.h"

int main()
{
    const unsigned short width = 256;
    const unsigned short height = 256;
    const unsigned short maxColor = 255;
    
    PPMImage img("P3", width, height, maxColor);

    img.writePPMHeaders(std::cout);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            img.writeColor(std::cout, Color(row, col, 0));
        }
    }
}
