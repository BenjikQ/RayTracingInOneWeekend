#include "color.hpp"

#include "random.hpp"

Color Color::random(double min, double max) {
    return Color{ ::random(min, max), ::random(min, max), ::random(min, max) };
}
