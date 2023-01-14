#ifndef RAYTRACINGINONEWEEKEND_MATERIALS_LAMBERTIAN_HPP
#define RAYTRACINGINONEWEEKEND_MATERIALS_LAMBERTIAN_HPP

#include "materials/material.hpp"
#include "utils/color.hpp"

struct Ray;
struct Hit;

class Lambertian : public Material {
    Color albedo_{};

public:
    explicit Lambertian(const Color& albedo)
        : albedo_{ albedo }
    {}

    [[nodiscard]] bool scatter(const Ray& in, const Hit& hit,
                                Color& attenuation, Ray& scattered) const override;
};


#endif //RAYTRACINGINONEWEEKEND_MATERIALS_LAMBERTIAN_HPP
