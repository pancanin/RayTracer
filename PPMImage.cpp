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
