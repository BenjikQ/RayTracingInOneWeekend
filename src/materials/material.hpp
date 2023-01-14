#ifndef RAYTRACINGINONEWEEKEND_MATERIALS_MATERIAL_HPP
#define RAYTRACINGINONEWEEKEND_MATERIALS_MATERIAL_HPP

#include <memory>

#include "geometry/vec3.hpp"

class Color;
struct Hit;
struct Ray;

class Material {
public:
    [[nodiscard]] virtual bool scatter(const Ray& in, const Hit& hit,
                                       Color& attenuation, Ray& scattered) const = 0;
    virtual ~Material() = default;
};

template<typename T, typename... Ts>
std::unique_ptr<T> create_material(Ts&&... ts) {
    return std::make_unique<T>(std::forward<Ts>(ts)...);
}

#endif //RAYTRACINGINONEWEEKEND_MATERIALS_MATERIAL_HPP
