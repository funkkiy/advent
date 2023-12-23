#pragma once

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <string>

namespace Advent {

template <typename... Types> void Print(std::string_view s, const Types... args)
{
    fmt::print(
        fg(fmt::color::green) | fmt::emphasis::italic, std::string(s), args...);
}

template <typename... Types>
void PrintLnUndecorated(std::string_view s, const Types... args)
{
    Print(s, args...);
    Print("\n");
}

template <typename... Types>
void PrintLn(std::string_view s, const Types... args)
{

    fmt::print(fg(fmt::color::yellow), "* ");
    PrintLnUndecorated(s, args...);
}

} // namespace Advent