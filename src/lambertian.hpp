#ifndef RAYTRACINGINONEWEEKEND_LAMBERTIAN_HPP
#define RAYTRACINGINONEWEEKEND_LAMBERTIAN_HPP

#include "material.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Lambertian : public Material {
    Color albedo_{};

public:
    explicit Lambertian(const Color& albedo)
        : albedo_{ albedo }
    {}

    [[nodiscard]] bool scatter(const Ray& in, const Shape::Hit& hit,
                                Color& attenuation, Ray& scattered) const override;
};


#endif //RAYTRACINGINONEWEEKEND_LAMBERTIAN_HPP
