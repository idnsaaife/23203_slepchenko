#include "beaconpattern.h"
#include "patternregistrar.h"
#include "factory.h"

#include <string>

std::vector<std::vector<bool>> BeaconPattern::createPattern(int rows, int cols) const
{
    std::vector<std::vector<bool>> pattern(rows, std::vector<bool>(cols, false));
    if (rows >= 4 && cols >= 4)
    {
        int centerRow = rows / 2;
        int centerCol = cols / 2;

        pattern[centerRow - 1][centerCol - 1] = true;
        pattern[centerRow - 1][centerCol] = true;
        pattern[centerRow][centerCol - 1] = true;
        pattern[centerRow][centerCol] = true;

        pattern[centerRow + 1][centerCol + 1] = true;
        pattern[centerRow + 1][centerCol + 2] = true;
        pattern[centerRow + 2][centerCol + 1] = true;
        pattern[centerRow + 2][centerCol + 2] = true;
    }
    return pattern;
}

namespace {
PatternRegistrar<BeaconPattern> BeaconPatternRegistrar("Beacon");
}

