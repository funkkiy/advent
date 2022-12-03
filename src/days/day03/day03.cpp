#include "day03.h"

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>
#include <map>

#include "../common/common.h"

namespace Advent::Day03 {

std::string commonCharacters(const std::string& a, const std::string& b)
{
    std::map<char, bool> seenCharacters;
    std::string commonCharacters;
    for (auto c : a) {
        if (seenCharacters[c]) {
            continue;
        }
        if (std::find(b.begin(), b.end(), c) != b.end()) {
            seenCharacters[c] = true;
            commonCharacters.push_back(c);
        }
    }
    return commonCharacters;
}

int calculatePriority(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 27;
    }
    return 0;
}

int part1(const std::string& input)
{
    int priorityTotal = 0;
    for (auto s : input | std::views::split(std::string_view{"\n"})) {
        // Obtain the first and second compartments from the input line
        std::string rucksack = std::string(s.data(), s.size());
        std::string firstHalf = rucksack.substr(0, rucksack.length() / 2);
        std::string secondHalf = rucksack.substr(rucksack.length() / 2);

        // Add to the priorityTotal *only* if the item hasn't been found before
        std::map<char, bool> alreadyFound;
        for (auto const& c : firstHalf) {
            // If the item has been found before
            if (alreadyFound[c]) {
                continue;
            }
            if (std::find(secondHalf.begin(), secondHalf.end(), c) !=
                secondHalf.end()) {
                priorityTotal += calculatePriority(c);
                alreadyFound[c] = true;
            }
        }
    }

    Advent::PrintLn("Priority: {}", priorityTotal);
    return 0;
}

int part2(const std::string& input)
{
    int priorityTotal = 0;
    auto lines = input | std::views::split(std::string_view{"\n"});
    for (auto lineIt = lines.begin(); lineIt != lines.end();) {
        // Split lines into three-element groups
        std::vector<std::string> group;
        for (int i = 0; i < 3; i++) {
            group.push_back(std::ranges::to<std::string>(*lineIt));
            lineIt++;
        }

        std::string commonFirst = commonCharacters(group[0], group[1]);
        std::string common = commonCharacters(commonFirst, group[2]);
        for (auto c : common) {
            priorityTotal += calculatePriority(c);
        }
    }

    Advent::PrintLn("Priority: {}", priorityTotal);
    return 0;
}

}  // namespace Advent::Day03