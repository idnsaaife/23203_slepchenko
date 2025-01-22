#include "headers/loader.h"

bool Loader::loadDynamicStrategyConfig(const std::string &configFilePath)
{
    std::ifstream jsonFile(configFilePath);
    if (!jsonFile)
    {
        return false;
    }
    jsonFile >> file;
    jsonFile.close();
    return true;
}

nlohmann::json Loader::getConfig() const
{
    return file;
}