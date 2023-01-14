#include "lambertian.hpp"

#include "geometry/hit.hpp"
#include "geometry/ray.hpp"

bool Lambertian::scatter(const Ray& in, const Hit& hit, Color& attenuation, Ray& scattered) const {
    auto scatter_direction = hit.normal + normalized(random_in_unit_sphere());
    if (scatter_direction.near_zero()) {
        scatter_direction = hit.normal;
    }
    scattered = Ray{ hit.point, scatter_direction };
    attenuation = albedo_;
    return true;
}
