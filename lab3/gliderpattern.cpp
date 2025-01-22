#include "gliderpattern.h"
#include "patternregistrar.h"
#include "factory.h"

#include <Qstring>

std::vector<std::vector<bool>> GliderPattern::createPattern(int rows, int cols) const
{
    std::vector<std::vector<bool>> pattern(rows, std::vector<bool>(cols, false));
    if (rows >= 3 && cols >= 3)
    {
        int centerRow = rows / 2;
        int centerCol = cols / 2;

        pattern[centerRow - 1][centerCol] = true;
        pattern[centerRow][centerCol + 1] = true;
        pattern[centerRow + 1][centerCol - 1] = true;
        pattern[centerRow + 1][centerCol] = true;
        pattern[centerRow + 1][centerCol + 1] = true;
    }
    return pattern;
}

namespace {
PatternRegistrar<GliderPattern> GliderPatternRegistrar("Glider");
}

