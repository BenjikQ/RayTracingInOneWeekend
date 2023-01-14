#include "vec3.hpp"

#include "utils/random.hpp"

Vec3 Vec3::random(double min, double max) {
    return Vec3{ ::random(min, max), ::random(min, max), ::random(min, max) };
}

Vec3 random_in_unit_sphere() {
    while (true) {
        auto p = Vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}
