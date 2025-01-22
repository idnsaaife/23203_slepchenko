#include "oscillatorpattern.h"
#include "patternregistrar.h"
#include "factory.h"

#include <string>

std::vector<std::vector<bool>> OscillatorPattern::createPattern(int rows, int cols) const
{
    std::vector<std::vector<bool>> pattern(rows, std::vector<bool>(cols, false));
    if (rows >= 3 && cols >= 3)
    {
        int centerRow = rows / 2;
        int centerCol = cols / 2;

        pattern[centerRow][centerCol - 1] = true;
        pattern[centerRow][centerCol] = true;
        pattern[centerRow][centerCol + 1] = true;
    }
    return pattern;
}

namespace {
    PatternRegistrar<OscillatorPattern> OscillatorPatternRegistrar("Oscillator");
}
