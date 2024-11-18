#pragma once
#include <iostream>

using Key = std::string;

class Value
{
public:
    Value(const unsigned &a, const unsigned &w) : age(a), weight(w) {};
    Value(const Value &other) = default;
    Value(Value &&other) = delete;
    Value() = default;
    ~Value() = default;
    Value &operator=(const Value &other) = delete;
    Value &operator=(Value &&other) = delete;
    friend bool operator==(const Value &v1, const Value &v2);
    friend bool operator!=(const Value &v1, const Value &v2);

private:
    unsigned age = 0;
    unsigned weight = 0;
};

class List
{
private:
    struct Node
    {
        Node(const Key &name, const Value &data) : key(name), value(data) {}
        Node(const Node &other) = delete;
        Node(Node &&other) = delete;
        Node &operator=(const Node &other) = delete;
        Node &operator=(Node &&other) = delete;
        ~Node() = default;
        Key key;
        Value value;
        Node *next = nullptr;
    };
    Node *first = nullptr;

public:
    List() = default;
    ~List();
    List(const List &b);
    List(List &&b) = delete;

    List &operator=(const List &other);
    List &operator=(List &&other) = delete;

    void pushBack(const Key &name, const Value &data);
    [[nodiscard]] bool contains(const Key &name) const;
    void clear();
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] const Value &findByKey(const Key &name) const;
    [[nodiscard]] const Key &getFirstKey() const;
    [[nodiscard]] const Value &getFirstValue() const;
    void removeFirst();
    bool remove(const Key &k);
};
