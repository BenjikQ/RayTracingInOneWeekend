#include "random.hpp"

#include <random>

#include "pcg_random.hpp"

static thread_local pcg_extras::seed_seq_from<std::random_device> seed_source;
static thread_local pcg32 rng{ seed_source };

double random(double min, double max) {
    std::uniform_real_distribution<double> dist{ min, max };
    return dist(rng);
}
