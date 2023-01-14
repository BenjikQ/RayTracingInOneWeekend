#include "random.hpp"

#include <random>

static thread_local std::mt19937 gen{ std::random_device{}() };

double random(double min, double max) {
    std::uniform_real_distribution<double> dist{ min, max };
    return dist(gen);
}
