# Understandable Ray Tracer

Create a bare-minimum ray tracer for learning graphics programming.
RT is a program that takes 3D objects and creates a 2D image based on camera, lighting, materials and more.

## 1. The output format

We choose PPM images as an output of our RT.

Create a class, may be called `PPMImage`, that handles writing to output stream the correct format for a PPM file.

```cpp
#include <string>
#include <ostream>

class PPMImage {
public:
	PPMImage(
		const std::string& colorFormat,
		unsigned short imgWidth,
		unsigned short imgHeight,
		unsigned short maxColor
	);

	void writePPMHeaders(std::ostream& os);
	void writeColor(std::ostream& os, unsigned short r, unsigned short g, unsigned short b);
private:
	std::string colorFormat;
	unsigned short imgWidth;
	unsigned short imgHeight;
	unsigned short maxColor;
};
```

```cpp
#include "PPMImage.h"

PPMImage::PPMImage(
	const std::string& colorFormat,
	unsigned short imgWidth,
	unsigned short imgHeight,
	unsigned short maxColor
): colorFormat(colorFormat), imgWidth(imgWidth), imgHeight(imgHeight), maxColor(maxColor) {}

void PPMImage::writePPMHeaders(std::ostream& os) {
	os << colorFormat << std::endl
		<< imgWidth << " " << imgHeight << std::endl
		<< std::to_string(maxColor) << std::endl;
}

void PPMImage::writeColor(std::ostream& os, unsigned short r, unsigned short g, unsigned short b) {
	os << r << " " << g << " " << b << std::endl;
}
```

In the main method we create a .ppm image and write the colors of bulgarian flag based on height.

```cpp
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
```

By redirecting std::cout to a file we get an ppm image.

![writing BG flag to file](https://github.com/pancanin/RayTracer/blob/master/helpful_materials/bg-flag.PNG?raw=true)

### Simple positional shader based on ray

![positional shader](https://github.com/pancanin/RayTracer/blob/master/helpful_materials/positional-shader.PNG?raw=true)

### Shader based on distance of ray from focal ray.

![positional shader](https://github.com/pancanin/RayTracer/blob/master/helpful_materials/distance-center.PNG?raw=true)