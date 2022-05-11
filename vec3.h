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

	/*
	* Follows from pythagorean theorem.
	*/
	double length() const {
		return std::sqrt(components_squared());
	}

	double components_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	/*
	* Return true if the vector is close to zero in all dimensions.
	*/
	bool near_zero() const {
		const auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}
private:
	double e[3];
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}

inline vec3 unitVector(const vec3& u) {
	return u / u.length();
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
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

// Mirror reflection. See README for more info on why this formula.
inline static vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2.0 * dot(v, n) * n;
}

inline vec3 random() {
	return vec3(random_double(), random_double(), random_double());
}

inline vec3 random(double min, double max) {
	return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

inline vec3 random_in_unit_sphere() {
	while (true) {
		auto p = random(-1, 1);
		if (p.components_squared() > 1) continue;
		return p;
	}
}

inline vec3 random_unit_vector() {
	return unitVector(random_in_unit_sphere());
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.components_squared())) * n;
	return r_out_perp + r_out_parallel;
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
