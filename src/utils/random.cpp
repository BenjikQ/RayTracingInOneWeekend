#include "random.hpp"

double random(double min, double max) {
    std::uniform_real_distribution<double> dist{ min, max };
    return dist(gen);
}
