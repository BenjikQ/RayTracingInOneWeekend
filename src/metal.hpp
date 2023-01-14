#ifndef RAYTRACINGINONEWEEKEND_METAL_HPP
#define RAYTRACINGINONEWEEKEND_METAL_HPP

#include "material.hpp"
#include "vec3.hpp"

class Metal : public Material {
    Color albedo_{};
    double fuzziness_{};

public:
    Metal(const Color& albedo, double fuzziness)
        : albedo_{ albedo }
        , fuzziness_{ fuzziness }
    {}

    [[nodiscard]] bool scatter(const Ray& in, const Shape::Hit& hit,
                               Color& attenuation, Ray& scattered) const override;
};


#endif //RAYTRACINGINONEWEEKEND_METAL_HPP
