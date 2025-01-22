#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

class Loader
{
private:
    nlohmann::json file;

public:
    Loader() = default;
    ~Loader() = default;
    bool loadDynamicStrategyConfig(const std::string &configFilePath);
    nlohmann::json getConfig() const;
};