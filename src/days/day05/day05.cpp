#include "day05.h"

#include <ranges>
#include <string>
#include <vector>

#include "../common/common.h"

namespace Advent::Day05 {

int part1(const std::string& input)
{
    auto newlineView = input | std::views::split(std::string_view{"\n"});

    // Initialize the crate stacks with the proper amount of stacks
    std::string firstLine = std::ranges::to<std::string>(*newlineView.begin());
    int stackMax = (static_cast<int>(firstLine.length() + 1) / 4);
    std::vector<std::vector<char>> crateStacks(stackMax, std::vector<char>());
    for (auto s : newlineView) {
        std::string line = std::ranges::to<std::string>(s);

        // Skip lines that we don't need
        if (line == "" || line.starts_with(" 1")) {
            continue;
        }

        // First, parse the crate stacks into their respective vector
        if (line.contains("[")) {
            for (int i = 0; i < stackMax; i++) {
                char crateMark = line[1 + (i * 4)];
                if (crateMark != ' ') {
                    crateStacks[i].insert(crateStacks[i].begin(), crateMark);
                }
            }
        }

        // Next, parse the move commands
        if (line.starts_with("move")) {
            int cratesMoved = std::stoi(line.substr(5, line.find(" from") - 5));
            int fromIdx = std::stoi(
                line.substr(line.find("from ") + 5,
                            line.find(" to") - line.find("from ") - 5));
            int toIdx = std::stoi(line.substr(line.find("to ") + 3));

            auto& fromStack = crateStacks[fromIdx - 1];
            auto& toStack = crateStacks[toIdx - 1];
            for (int i = 0; i < cratesMoved; i++) {
                char sourceLast = fromStack[fromStack.size() - 1];
                fromStack.pop_back();
                toStack.push_back(sourceLast);
            }
        }
    }

    // Print out the top crates from each stack
    std::string topCrates;
    for (auto& stack : crateStacks) {
        topCrates.push_back(stack[stack.size() - 1]);
    }
    Advent::PrintLn("Top Crates: {}", topCrates);

    return 0;
}

int part2(const std::string& input)
{
    auto newlineView = input | std::views::split(std::string_view{"\n"});

    // Initialize the crate stacks with the proper amount of stacks
    std::string firstLine = std::ranges::to<std::string>(*newlineView.begin());
    int stackMax = (static_cast<int>(firstLine.length() + 1) / 4);
    std::vector<std::vector<char>> crateStacks(stackMax, std::vector<char>());
    for (auto s : newlineView) {
        std::string line = std::ranges::to<std::string>(s);

        // Skip lines that we don't need
        if (line == "" || line.starts_with(" 1")) {
            continue;
        }

        // First, parse the crate stacks into their respective vector
        if (line.contains("[")) {
            for (int i = 0; i < stackMax; i++) {
                char crateMark = line[1 + (i * 4)];
                if (crateMark != ' ') {
                    crateStacks[i].insert(crateStacks[i].begin(), crateMark);
                }
            }
        }

        // Next, parse the move commands
        if (line.starts_with("move")) {
            int cratesMoved = std::stoi(line.substr(5, line.find(" from") - 5));
            int fromIdx = std::stoi(
                line.substr(line.find("from ") + 5,
                            line.find(" to") - line.find("from ") - 5));
            int toIdx = std::stoi(line.substr(line.find("to ") + 3));

            auto& fromStack = crateStacks[fromIdx - 1];
            auto& toStack = crateStacks[toIdx - 1];
            for (int i = cratesMoved; i > 0; i--) {
                size_t sourceTopIdx = fromStack.size() - i;
                char sourceTop = fromStack[sourceTopIdx];
                fromStack.erase(fromStack.begin() + sourceTopIdx);
                toStack.push_back(sourceTop);
            }
        }
    }

    // Print out the top crates from each stack
    std::string topCrates;
    for (auto& stack : crateStacks) {
        topCrates.push_back(stack[stack.size() - 1]);
    }
    Advent::PrintLn("Top Crates: {}", topCrates);

    return 0;
}

}  // namespace Advent::Day05