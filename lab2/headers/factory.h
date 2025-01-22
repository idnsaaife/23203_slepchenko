#pragma once
#include <map>
#include "nlohmann/json.hpp"
template <class Key, class Product>
class Factory
{
public:
    static Factory *getInstance()
    {
        static Factory f;
        return &f;
    }

    void registStrategy(const Key &name, std::function<Product *()> creator)
    {
        creators_[name] = creator;
    }

    std::unique_ptr<Product> createStrategyByName(const Key &name)
    {
        auto &creator = creators_.at(name);
        return std::unique_ptr<Product>(creator());
    };
    
    
    void registConfigStrategy(const Key &name, std::function<Product *(const nlohmann::json &)> creator)
    {
        dynamicCreators_[name] = creator;
    }
    
    std::unique_ptr<Product> createStrategyByConfig(const Key &name, const nlohmann::json &config)
    {
        auto &creator = dynamicCreators_.at(name);
        return std::unique_ptr<Product>(creator(config));
    };

    
    

private:
    Factory() = default;
    ~Factory() = default;
    Factory(const Factory &) = delete;
    Factory &operator=(const Factory &) = delete;
    Factory(Factory &&) = delete;
    Factory &operator=(Factory &&) = delete;
    std::unordered_map<Key, std::function<Product *()>> creators_;
    std::unordered_map<Key, std::function<Product *(const nlohmann::json &)>> dynamicCreators_;
};

