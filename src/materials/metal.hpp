#ifndef RAYTRACINGINONEWEEKEND_MATERIALS_METAL_HPP
#define RAYTRACINGINONEWEEKEND_MATERIALS_METAL_HPP

#include "materials/material.hpp"
#include "utils/color.hpp"

struct Hit;
struct Ray;

class Metal : public Material {
    Color albedo_{};
    double fuzziness_{};

public:
    Metal(const Color& albedo, double fuzziness)
        : albedo_{ albedo }
        , fuzziness_{ fuzziness }
    {}

    [[nodiscard]] bool scatter(const Ray& in, const Hit& hit,
                               Color& attenuation, Ray& scattered) const override;
};


#endif //RAYTRACINGINONEWEEKEND_MATERIALS_METAL_HPP
