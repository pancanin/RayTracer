#pragma once

#include <string>
#include <ostream>

#include ""

class ppm_image {
public:
	ppm_image(const std::string& colorFormat, unsigned short maxColor, int imgW, int imgH);

	void writePPMHeaders(std::ostream& os);

private:
	std::string colorFormat;
	unsigned short maxColor;
	int imgW;
	int imgH;
};

ppm_image::ppm_image(const std::string& colorFormat, unsigned short maxColor, int imgW, int imgH) :
	colorFormat(colorFormat), maxColor(maxColor), imgW(imgW), imgH(imgH) {}

void ppm_image::writePPMHeaders(std::ostream& os) {
	os << "P3" << std::endl << imgW << " " << imgH << std::endl << std::to_string(maxColor) << std::endl;
}

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Divide the color by the number of samples.
	auto scale = 1.0 / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);
	// Write the translated [0,255] value of each color component.
	out << static_cast<int>(255.999 * clamp(r, 0, 0.999)) << ' '
		<< static_cast<int>(255.999 * clamp(g, 0, 0.999)) << ' '
		<< static_cast<int>(255.999 * clamp(b, 0, 0.999)) << '\n';
}