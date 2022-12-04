#include "day04.h"

#include <ranges>
#include <string>

#include "../common/common.h"

namespace Advent::Day04 {

struct ElfAssignment {
    int firstSection;
    int lastSection;
};

ElfAssignment assignmentFromString(const std::string& s)
{
    auto split = (s | std::views::split(std::string_view{"-"}));
    auto splitIt = split.begin();
    return ElfAssignment{
        .firstSection = std::stoi(std::ranges::to<std::string>(*splitIt)),
        .lastSection = std::stoi(std::ranges::to<std::string>(*(++splitIt)))};
}

int part1(const std::string& input)
{
    int fullyContainTotal = 0;
    for (auto s : input | std::views::split(std::string_view{"\n"})) {
        auto elves = (s | std::views::split(std::string_view{","}));
        auto elvesIt = elves.begin();
        ElfAssignment first =
            assignmentFromString(std::ranges::to<std::string>(*elvesIt));
        ElfAssignment second =
            assignmentFromString(std::ranges::to<std::string>(*(++elvesIt)));

        if (first.firstSection <= second.firstSection &&
            first.lastSection >= second.lastSection) {
            fullyContainTotal++;
        } else if (second.firstSection <= first.firstSection &&
                   second.lastSection >= first.lastSection) {
            fullyContainTotal++;
        }
    }

    Advent::PrintLn("Fully Contained: {}", fullyContainTotal);
    return 0;
}

int part2(const std::string& input)
{
    int overlapTotal = 0;
    for (auto s : input | std::views::split(std::string_view{"\n"})) {
        auto elves = (s | std::views::split(std::string_view{","}));
        auto elvesIt = elves.begin();
        ElfAssignment first =
            assignmentFromString(std::ranges::to<std::string>(*elvesIt));
        ElfAssignment second =
            assignmentFromString(std::ranges::to<std::string>(*(++elvesIt)));

        if (first.firstSection <= second.lastSection && second.firstSection <= first.lastSection) {
            overlapTotal++;
        }
    }

    Advent::PrintLn("Overlapping: {}", overlapTotal);
    return 0;
}

}  // namespace Advent::Day04