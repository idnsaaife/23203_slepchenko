#ifndef PATTERN_H
#define PATTERN_H

#include <vector>

class Pattern
{
public:
    Pattern() = default;
    virtual ~Pattern() = default;
    virtual std::vector<std::vector<bool>> createPattern(int rows, int cols) const = 0;
};

#endif // PATTERN_H
