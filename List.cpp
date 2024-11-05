#include "List.hpp"
#include <iostream>

typedef std::string Key;

Value::Value(const Value &other)
{
    age = other.age;
    weight = other.weight;
}

bool operator==(const Value &v1, const Value &v2)
{
    if (v1.age != v2.age)
        return false;
    if (v1.weight != v2.weight)
        return false;
    return true;
}

bool operator!=(const Value &v1, const Value &v2)
{
    return !(v1 == v2);
}

class Node
{
public:
    Node(const Key &name, const Value &data) : key(name), value(data), next(nullptr) {};
    Node(const Node &other) : key(other.key), value(other.value), next(nullptr)
    {
        if (other.next)
        {
            next = new Node(*other.next); 
        }
    }
    Node *getNext()
    {
        return this->next;
    }
    void pushAfter(Node *n) { this->next = n; }
    Value &getValue() { return this->value; }
    Key &getKey() { return this->key; }

private:
    Key key;
    Value value;
    Node *next;
};

List::List(const List &b) 
{
    first = nullptr;

    if (b.first == nullptr)
    {
        return;
    }
    first = new Node(*b.first);
}

List::~List()
{
    while (first != nullptr)
    {
        removeFirst();
    }
}



List &List::operator=(const List &other)
{
    if (this == &other)
        return *this;

    while (first != nullptr)
    {
        removeFirst();
    }
    if (other.first != nullptr)
    {
        first = new Node(*other.first);
    }
    return *this;
}

bool List::isEmpty()
{
    return (nullptr == first);
}

bool List::pushBack(const Key &name, const Value &data)
{
    Node *p = new Node(name, data);
    if (isEmpty())
    {
        first = p;
        return true;
    }
    Node *current = first;
    while (current->getNext() != nullptr)
    {
        current = current->getNext();
    }
    current->pushAfter(p);
    return true;
}

bool List::contains(const Key &name)
{
    Node *p = first;
    while (p != nullptr)
    {
        if (p->getKey() == name)
            return true;
        p = p->getNext();
    }
    return false;
}

Value &List::findByKey(const Key &name)
{

    Node *p = first;
    while (p != nullptr)
    {
        if (p->getKey() == name)
            return p->getValue();
        p = p->getNext();
    }
    static Value v;
    return v;
}

void List::removeFirst()
{
    if (isEmpty())
        return;
    Node *p = first;
    first = p->getNext();
    delete p;
}

Value &List::getFirstValue()
{
    return first->getValue();
}

Key &List::getFirstKey()
{
    return first->getKey();
}

bool List::remove(const Key &k)
{
    if (isEmpty())
    {
        return false;
    }

    if (first->getKey() == k)
    {
        removeFirst();
        return true;
    }
    Node *slow = first;
    Node *fast = first->getNext();
    while (fast && fast->getKey() != k)
    {
        fast = fast->getNext();
        slow = slow->getNext();
    }

    if (fast == nullptr)
    {
        return false;
    }
    slow->pushAfter(fast->getNext());
    delete fast;
    return true;
}
