#ifndef BEACONPATTERN_H
#define BEACONPATTERN_H

#include "patternregistrar.h"
#include "pattern.h"
#include "factory.h"

class BeaconPattern : public Pattern
{
public:
    BeaconPattern() = default;
    std::vector<std::vector<bool>> createPattern(int rows, int cols) const override;
};


#endif // BEACONPATTERN_H
