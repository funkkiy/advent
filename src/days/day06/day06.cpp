#include "day06.h"

#include <string>
#include <vector>
#include <algorithm>

#include "../common/common.h"

namespace Advent::Day06 {

bool isPacketMarker(const std::string& s) {
    std::vector<char> seenBefore;
    for (char c : s) {
        if (std::find(seenBefore.begin(), seenBefore.end(), c) != seenBefore.end()) {
            return false;
        }
        seenBefore.push_back(c);
    }
    return true;
}

int part1(const std::string& input)
{
    for (auto inputIt = input.begin(); inputIt != input.end() - 4; inputIt++) {
        std::string marker = std::string(inputIt, inputIt + 4);
        if (isPacketMarker(marker)) {
            Advent::PrintLn("Marker At: {}", (inputIt + 4) - input.begin());
            break;
        }
    }
    return 0;
}

int part2(const std::string& input)
{
    for (auto inputIt = input.begin(); inputIt != input.end() - 14; inputIt++) {
        std::string marker = std::string(inputIt, inputIt + 14);
        if (isPacketMarker(marker)) {
            Advent::PrintLn("Marker At: {}", (inputIt + 14) - input.begin());
            break;
        }
    }
    return 0;
}

}  // namespace Advent::Day06