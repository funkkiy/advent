#include <fmt/color.h>
#include <fmt/core.h>

#include <array>
#include <fstream>
#include <vector>

#include "days/day01/day01.h"
#include "days/day02/day02.h"
#include "days/day03/day03.h"
#include "days/day04/day04.h"
#include "days/day05/day05.h"
#include "days/day06/day06.h"
#include "days/day07/day07.h"

using SolverFn = int (*)(const std::string&);
std::array<std::vector<SolverFn>, 7> days = {
    std::vector({Advent::Day01::part1, Advent::Day01::part2}),  // Day 1
    std::vector({Advent::Day02::part1, Advent::Day02::part2}),  // Day 2
    std::vector({Advent::Day03::part1, Advent::Day03::part2}),  // Day 3
    std::vector({Advent::Day04::part1, Advent::Day04::part2}),  // Day 4
    std::vector({Advent::Day05::part1, Advent::Day05::part2}),  // Day 5
    std::vector({Advent::Day06::part1, Advent::Day06::part2}),  // Day 6
    std::vector({Advent::Day07::part1})                         // Day 7
};

int main(int argc, char* argv[])
{
    size_t runningDay = 1;
    size_t runningPart = 1;
    std::string inputPath;
    if (argc <= 3) {
        // Run the latest implemented day and part
        runningDay = days.size();
        runningPart = days.at(runningDay - 1).size();
        inputPath = fmt::format("day{:02d}.txt", runningDay);
    } else {
        // Accept user input for day, part and path
        runningDay = std::atoi(argv[1]);
        runningPart = std::atoi(argv[2]);
        inputPath = argv[3];
    }

    fmt::print(fg(fmt::color::crimson), "[ * ] Running Day {}, Part {}\n",
               runningDay, runningPart);
    std::ifstream inputStream = std::ifstream(inputPath, std::ios::in);
    if (inputStream) {
        std::string inputContents = {
            std::istreambuf_iterator<char>(inputStream),
            std::istreambuf_iterator<char>()};
        // If present, remove the last empty line
        size_t lastCharacterIdx = inputContents.length() - 1;
        if (inputContents[lastCharacterIdx] == '\n') {
            inputContents = inputContents.substr(0, lastCharacterIdx);
        }
        return days.at(runningDay - 1)[runningPart - 1](inputContents);
    }

    return -1;
}