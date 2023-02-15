#ifndef RAYTRACINGINONEWEEKEND_UTILS_RANDOM_HPP
#define RAYTRACINGINONEWEEKEND_UTILS_RANDOM_HPP

#include <random>

static std::mt19937 gen{ std::random_device{}() };

[[nodiscard]] double random(double min, double max);

#endif //RAYTRACINGINONEWEEKEND_UTILS_RANDOM_HPP
