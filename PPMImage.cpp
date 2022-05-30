#include "PPMImage.h"

PPMImage::PPMImage(
	unsigned short imgWidth,
	unsigned short imgHeight,
	unsigned short maxColor
): colorFormat("P3"), imgWidth(imgWidth), imgHeight(imgHeight), maxColor(maxColor) {}

void PPMImage::writePPMHeaders(std::ostream& os) {
	os << colorFormat << std::endl
		<< imgWidth << " " << imgHeight << std::endl
		<< std::to_string(maxColor) << std::endl;
}

void PPMImage::writeColor(std::ostream& os, const Color& color) {
	os << color.x() << " " << color.y() << " " << color.z() << std::endl;
}
