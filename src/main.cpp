#include <cstdint>

#include <indicators/cursor_control.hpp>
#include <indicators/progress_bar.hpp>

#include <range/v3/all.hpp>

#include "image.hpp"

using namespace indicators;

[[nodiscard]] ProgressBar create_progress_bar(std::int32_t max_progress) noexcept {
    return ProgressBar{
        option::BarWidth{ 50 },
        option::Start{ "[" },
        option::Fill{ "=" },
        option::Lead{ ">" },
        option::Remainder{ " " },
        option::End{ "]" },
        option::ForegroundColor{ indicators::Color::green },
        option::ShowElapsedTime{ true },
        option::ShowPercentage{ true },
        option::MaxProgress{ max_progress },
        option::FontStyles{std::vector<FontStyle>{ FontStyle::bold } },
    };
}

int main() {
    constexpr std::int32_t image_width{ 256 };
    constexpr std::int32_t image_height{ 256 };

    Image image{ image_width, image_height };

    show_console_cursor(false);
    auto bar = create_progress_bar(image_height);

    auto rows = ranges::view::iota(0, image_height);
    auto columns = ranges::view::iota(0, image_width);
    auto rng = ranges::view::cartesian_product(rows, columns);

    for (auto&& [row, col] : rng) {
        const auto r = static_cast<double>(col) / (image_width - 1);
        const auto g = static_cast<double>(image_height - row) / (image_height - 1);
        const auto b = 0.2;

        image.set_pixel(row, col, { r, g, b });

        if (col == 0) {
            bar.tick();
        }
    }

    image.save("image.png");

    show_console_cursor(true);

    return 0;
}
