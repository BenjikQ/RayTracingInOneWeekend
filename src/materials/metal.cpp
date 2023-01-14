#include "metal.hpp"

#include "geometry/hit.hpp"
#include "geometry/ray.hpp"

bool Metal::scatter(const Ray& in, const Hit& hit, Color& attenuation, Ray& scattered) const {
    Vec3 reflected{ reflect(normalized(in.direction), hit.normal) };
    scattered = Ray{ hit.point, reflected + fuzziness_ * random_in_unit_sphere() };
    attenuation = albedo_;
    return dot(scattered.direction, hit.normal) > 0;
}
