#include <fmt/color.h>
#include <fmt/core.h>

#include <array>
#include <fstream>
#include <vector>

#include "days/day01/day01.h"

using SolverFn = int (*)(const std::string&);
std::array<std::vector<SolverFn>, 1> days = {
    std::vector({Advent::Day01::part1, Advent::Day01::part2})  // Day 1
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
        return days.at(runningDay - 1)[runningPart - 1](inputContents);
    }

    return -1;
}