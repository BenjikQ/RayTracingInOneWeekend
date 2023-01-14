#ifndef RAYTRACINGINONEWEEKEND_MATERIAL_HPP
#define RAYTRACINGINONEWEEKEND_MATERIAL_HPP

#include "shape.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Material {
public:
    [[nodiscard]] virtual bool scatter(const Ray& in, const Shape::Hit& hit,
                                       Color& attenuation, Ray& scattered) const = 0;
    virtual ~Material() = default;
};


#endif //RAYTRACINGINONEWEEKEND_MATERIAL_HPP
