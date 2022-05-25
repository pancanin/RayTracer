#include <iostream>

#include "PPMImage.h"

int main()
{
    const unsigned short width = 256;
    const unsigned short height = 256;
    const unsigned short maxColor = 255;
    
    PPMImage img("P3", width, height, maxColor);

    img.writePPMHeaders(std::cout);

    int heightThird = height / 3;
    int upperPartEnd = heightThird;
    int midPartEnd = heightThird * 2;
    int bottomPartEnd = height;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (row <= upperPartEnd) {
                img.writeColor(std::cout, 0xff, 0xff, 0xff);
            }
            else if (row <= midPartEnd) {
                img.writeColor(std::cout, 0, 0xff, 0);
            }
            else {
                img.writeColor(std::cout, 0xff, 0, 0);
            }
        }
    }
}
