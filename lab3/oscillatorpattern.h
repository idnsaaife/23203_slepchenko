#ifndef OSCILLATORPATTERN_H
#define OSCILLATORPATTERN_H

#include "patternregistrar.h"
#include "pattern.h"
#include "factory.h"

class OscillatorPattern : public Pattern
{
public:
    OscillatorPattern() = default;
    std::vector<std::vector<bool>> createPattern(int rows, int cols) const override;
};



#endif // OSCILLATORPATTERN_H
