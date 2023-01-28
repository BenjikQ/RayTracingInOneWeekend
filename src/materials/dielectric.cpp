#include "dielectric.hpp"

#include <cmath>

#include "geometry/hit.hpp"
#include "geometry/ray.hpp"
#include "geometry/vec3.hpp"
#include "utils/color.hpp"
#include "utils/random.hpp"

// Schlick's approximation
double reflectance(double cosine, double reflectance_index) {
    auto r0 = (1 - reflectance_index) / (1 + reflectance_index);
    r0 *= r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

bool Dielectric::scatter(const Ray& in, const Hit& hit, Color& attenuation, Ray& scattered) const {
    attenuation = Color{ 1.0, 1.0, 1.0 };
    const double refraction_ratio{ hit.front_face ? 1.0 / refraction_index_ : refraction_index_ };

    const Vec3 unit_direction{ normalized(in.direction) };
    const double cos_theta{ std::min(dot(-unit_direction, hit.normal), 1.0) };
    const double sin_theta{ std::sqrt(1 - cos_theta * cos_theta) };

    const bool cannot_refract{ refraction_ratio * sin_theta > 1.0 };
    const Vec3 direction{ (cannot_refract || reflectance(cos_theta, refraction_index_) > random(0.0, 1.0) ) ?
                          reflect(unit_direction, hit.normal) :
                          refract(unit_direction, hit.normal, refraction_ratio) };

    scattered = Ray{ hit.point, direction };
    return true;
}
