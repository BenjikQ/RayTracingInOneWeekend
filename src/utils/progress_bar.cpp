#include "progress_bar.hpp"

indicators::ProgressBar create_progress_bar(int max_progress) noexcept {
    using namespace indicators;

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
