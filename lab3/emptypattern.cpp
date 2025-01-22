#include "emptypattern.h"
#include "patternregistrar.h"
#include "factory.h"

#include <Qstring>

std::vector<std::vector<bool>> EmptyPattern::createPattern(int rows, int cols) const
{
    return std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
}

namespace {
PatternRegistrar<EmptyPattern> EmptyPatternRegistrar("Empty");
}
