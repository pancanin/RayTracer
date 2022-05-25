#pragma once

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
