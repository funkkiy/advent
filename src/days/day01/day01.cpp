#include "day01.h"

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

#include "../common/common.h"

namespace Advent::Day01 {

std::vector<int> common(const std::string& input)
{
    std::vector<int> calories = {};
    for (auto s : std::views::split(input, std::string_view{"\n\n"})) {
        int totalCalories = 0;
        for (auto c : std::views::split(s, std::string_view{"\n"})) {
            totalCalories += std::atoi(c.data());
        }
        calories.push_back(totalCalories);
    }
    std::sort(calories.begin(), calories.end());
    return calories;
}

int part1(const std::string& input)
{
    std::vector<int> calories = common(input);
    Advent::PrintLn("{}\n", calories[calories.size() - 1]);
    return 0;
}

int part2(const std::string& input)
{
    std::vector<int> calories = common(input);
    int a = calories[calories.size() - 1];
    int b = calories[calories.size() - 2];
    int c = calories[calories.size() - 3];
    Advent::PrintLn("{} + {} + {} = {}\n", a, b, c, a + b + c);
    return 0;
}

}  // namespace Advent::Day01