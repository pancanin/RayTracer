#pragma once

#include <cmath>
#include <iostream>

class vec3 {
public:
	vec3() : e{ 0, 0, 0 } {}
	vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int idx) const { return e[idx]; }
	double& operator[](int idx) { return e[idx]; }

	vec3& operator+=(const vec3& other) {
		e[0] += other[0];
		e[1] += other[1];
		e[2] += other[2];
		return *this;
	}

	vec3& operator*=(const double sc) {
		e[0] *= sc;
		e[1] *= sc;
		e[2] *= sc;
		return *this;
	}

	vec3& operator/=(const double sc) {
		return *this *= (1 / sc);
	}

	double length() const {
		return std::sqrt(length_squared());
	}

	double length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline static vec3 random() {
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max) {
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

	inline static vec3 random_in_unit_sphere() {
		while (true) {
			auto p = random(-1, 1);
			if (p.length_squared() > 1) continue;
			return p;
		}
	}

	double e[3];
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u[0] * v[0] +
		u[1] * v[1] +
		u[2] * v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(
		u[1] * v[2] - v[1] * u[2],
		u[0] * v[2] - v[0] * u[2],
		u[0] * v[1] - v[0] * u[1]
	);
}

inline vec3 unitVector(const vec3& u) {
	return u / u.length();
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
