#ifndef GLIDERPATTERN_H
#define GLIDERPATTERN_H

#include "patternregistrar.h"
#include "pattern.h"
#include "factory.h"

class GliderPattern : public Pattern
{
public:
    GliderPattern() = default;
    std::vector<std::vector<bool>> createPattern(int rows, int cols) const override;
};


#endif // GLIDERPATTERN_H
