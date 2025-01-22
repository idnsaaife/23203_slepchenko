#ifndef PATTERNREGISTRAR_H
#define PATTERNREGISTRAR_H

#include "factory.h"
#include "pattern.h"
#include <QString>

template <typename PatternType>
class PatternRegistrar
{
public:
    PatternRegistrar(const QString &name)
    {
        Factory<QString, Pattern>::getInstance()->registPattern(name, createPatternInstance);
    }

private:
    static Pattern *createPatternInstance()
    {
        return new PatternType();
    }
};

#endif // PATTERNREGISTRAR_H
