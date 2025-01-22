#ifndef EMPTYPATTERN_H
#define EMPTYPATTERN_H

#include "patternregistrar.h"
#include "pattern.h"
#include "factory.h"

class EmptyPattern : public Pattern
{
public:
    EmptyPattern() = default;
    std::vector<std::vector<bool>> createPattern(int rows, int cols) const override;
};


#endif // EMPTYPATTERN_H
