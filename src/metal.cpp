#include "metal.hpp"

bool Metal::scatter(const Ray& in, const Shape::Hit& hit, Color& attenuation, Ray& scattered) const {
    Vec3 reflected{ reflect(normalized(in.direction), hit.normal) };
    scattered = Ray{ hit.point, reflected + fuzziness_ * random_in_unit_sphere() };
    attenuation = albedo_;
    return dot(scattered.direction, hit.normal) > 0;
}
