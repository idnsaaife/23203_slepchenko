#include "factory.h"

template <class Key, class Product>
Factory<Key, Product> *Factory<Key, Product>::getInstance()
{
    static Factory f;
    return &f;
}

template <class Key, class Product>
void Factory<Key, Product>::registPattern(const Key &name, std::function<Product *()> creator)
{
    creators_[name] = creator;
}

template <class Key, class Product>
std::unique_ptr<Product> Factory<Key, Product>::createPatternByName(const Key &name)
{
    auto &creator = creators_.at(name);
    return std::unique_ptr<Product>(creator());
};
