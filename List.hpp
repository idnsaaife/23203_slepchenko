#pragma once
#include <iostream>

typedef std::string Key;

struct Value
{
public:
    Value(const unsigned &a, const unsigned &w) : age(a), weight(w) {};
    Value(const Value &other);
    Value() {};
    ~Value() {};
    friend bool operator==(const Value &v1, const Value &v2);
    friend bool operator!=(const Value &v1, const Value &v2);
    private:
    unsigned age = 0;
    unsigned weight = 0;
};

class Node;

class List
{
    private:
    Node *first;
    public:
    List() : first(nullptr) {};
    ~List();
    List(const List &b);
    List &operator=(const List &other);
    bool isEmpty();
    bool pushBack(const Key &name, const Value &data);
    bool contains(const Key &name);
    Value &findByKey(const Key &name);
    Key &getFirstKey();
    Value &getFirstValue();
    void removeFirst();
    bool remove(const Key &k);
};
