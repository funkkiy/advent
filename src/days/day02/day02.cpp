#include "day02.h"

#include <map>
#include <ranges>

#include "../common/common.h"

namespace Advent::Day02 {

enum class ActionType { Undefined = 0, Rock = 1, Paper = 2, Scissors = 3 };
enum class MatchOutcome { Undefined = 0, Loss = 1, Draw = 2, Win = 3 };

std::map<ActionType, ActionType> WinningMoves = {
    {ActionType::Rock, ActionType::Paper},
    {ActionType::Paper, ActionType::Scissors},
    {ActionType::Scissors, ActionType::Rock}};
std::map<ActionType, ActionType> LosingMoves = {
    {ActionType::Rock, ActionType::Scissors},
    {ActionType::Paper, ActionType::Rock},
    {ActionType::Scissors, ActionType::Paper}};

ActionType decodeAction(char encodedAction)
{
    switch (encodedAction) {
        case 'A':
        case 'X':
            return ActionType::Rock;
        case 'B':
        case 'Y':
            return ActionType::Paper;
        case 'C':
        case 'Z':
            return ActionType::Scissors;
        default:
            return ActionType::Undefined;
    }
}

MatchOutcome outcomeFromGuidance(char encodedGuidance)
{
    switch (encodedGuidance) {
        case 'X':
            return MatchOutcome::Loss;
        case 'Y':
            return MatchOutcome::Draw;
        case 'Z':
            return MatchOutcome::Win;
        default:
            return MatchOutcome::Undefined;
    }
}

MatchOutcome outcomeFromBattle(ActionType playerMove, ActionType enemyMove)
{
    if (playerMove == ActionType::Undefined || enemyMove == ActionType::Undefined) {
        return MatchOutcome::Undefined;
    }

    if (playerMove == enemyMove) {
        return MatchOutcome::Draw;
    }

    if (playerMove == WinningMoves[enemyMove]) {
        return MatchOutcome::Win;
    }

    return MatchOutcome::Loss;
}

int part1(const std::string& input)
{
    int totalScore = 0;
    for (auto s : std::views::split(input, std::string_view{"\n"})) {
        // s is formatted like: <enemy move> + ' ' + <player move>
        ActionType enemyMove = decodeAction(s[0]);
        ActionType playerMove = decodeAction(s[2]);

        switch (outcomeFromBattle(playerMove, enemyMove)) {
            case MatchOutcome::Win:
                totalScore += 6 + static_cast<int>(playerMove);
                break;
            case MatchOutcome::Draw:
                totalScore += 3 + static_cast<int>(playerMove);
                break;
            case MatchOutcome::Loss:
                totalScore += 0 + static_cast<int>(playerMove);
                break;
            case MatchOutcome::Undefined:
            default:
                break;
        }
    }

    Advent::PrintLn("Total Score: {}", totalScore);
    return 0;
}

int part2(const std::string& input)
{
    int totalScore = 0;
    for (auto s : std::views::split(input, std::string_view{"\n"})) {
        // s is formatted like: <enemy move> + ' ' + <outcome guidance>
        ActionType enemyMove = decodeAction(s[0]);
        MatchOutcome expectedOutcome = outcomeFromGuidance(s[2]);

        switch (expectedOutcome) {
            case MatchOutcome::Loss:
                totalScore += 0 + static_cast<int>(LosingMoves[enemyMove]);
                break;
            case MatchOutcome::Draw:
                totalScore += 3 + static_cast<int>(enemyMove);
                break;
            case MatchOutcome::Win:
                totalScore += 6 + static_cast<int>(WinningMoves[enemyMove]);
                break;
            case MatchOutcome::Undefined:
            default:
                break;
        }
    }

    Advent::PrintLn("Total Score: {}", totalScore);
    return 0;
}

}  // namespace Advent::Day02