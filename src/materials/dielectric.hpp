#ifndef RAYTRACINGINONEWEEKEND_MATERIALS_DIELECTRIC_HPP
#define RAYTRACINGINONEWEEKEND_MATERIALS_DIELECTRIC_HPP

#include "materials/material.hpp"

struct Color;
struct Hit;
struct Ray;

class Dielectric : public Material {
    double refraction_index_{};

public:
    explicit Dielectric(double refraction_index)
        : refraction_index_{ refraction_index }
    {}

    [[nodiscard]] bool scatter(const Ray& in, const Hit& hit,
                               Color& attenuation, Ray& scattered) const override;
};

#endif //RAYTRACINGINONEWEEKEND_MATERIALS_DIELECTRIC_HPP
