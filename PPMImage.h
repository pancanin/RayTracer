#pragma once

#include <string>
#include <ostream>

#include "Color.h"

class PPMImage {
public:
	PPMImage(
		const std::string& colorFormat,
		unsigned short imgWidth,
		unsigned short imgHeight,
		unsigned short maxColor
	);

	void writePPMHeaders(std::ostream& os);
	void writeColor(std::ostream& os, const Color& color);
private:
	std::string colorFormat;
	unsigned short imgWidth;
	unsigned short imgHeight;
	unsigned short maxColor;
};
