#pragma once

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <string>

namespace Advent {

template <typename... Types>
void PrintLn(std::string_view s, const Types... args)
{
    fmt::print(fg(fmt::color::yellow), "* ");
    fmt::print(fg(fmt::color::green) | fmt::emphasis::italic,
               std::string(s) + '\n', args...);
}

}  // namespace Advent