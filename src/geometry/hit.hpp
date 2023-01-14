#ifndef RAYTRACINGINONEWEEKEND_GEOMETRY_HIT_HPP
#define RAYTRACINGINONEWEEKEND_GEOMETRY_HIT_HPP

#include "geometry/point3.hpp"
#include "geometry/vec3.hpp"

class Material;
struct Ray;

struct Hit {
    Point3 point{};
    Vec3 normal{};
    const Material* material{};
    double t{};
    bool front_face{};

    void set_face_normal(const Ray& ray, const Vec3& outward_normal);
};


#endif //RAYTRACINGINONEWEEKEND_GEOMETRY_HIT_HPP
