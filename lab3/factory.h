#ifndef FACTORY_H
#define FACTORY_H

#include <functional>
#include <QMap>
#include <QString>

template <class Key, class Product>
class Factory
{
public:
    static Factory *getInstance()
    {
        static Factory f;
        return &f;
    }

    void registPattern(const Key &name, std::function<Product *()> creator)
    {
        creators_[name] = creator;
    }

    std::unique_ptr<Product> createPatternByName(const QString &name) {
        auto& creator = creators_.find(name).value();
        return std::unique_ptr<Product>(creator());
    }

private:
    Factory() = default;
    ~Factory() = default;
    Factory(const Factory &) = delete;
    Factory &operator=(const Factory &) = delete;
    Factory(Factory &&) = delete;
    Factory &operator=(Factory &&) = delete;
    QMap<Key, std::function<Product *()>> creators_;
};



#endif // FACTORY_H
