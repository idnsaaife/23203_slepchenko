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

Node::Node(const Node &other) : value(other.value), key(other.key), next(nullptr)
{
    if (other.next != nullptr)
    {
        next = new Node(*other.next);
    }
}

Node::Node(Node &&other) : key(std::move(other.key)), value(std::move(other.value)), next(other.next) 
{

    other.next = nullptr;
}

Node &Node::operator=(const Node &other)
{
    if (this == &other)
    {
        return *this;
    }
    key = other.key;
    value = other.value;
    if (nullptr != next)
    {
        delete next;
    }
    if (nullptr == other.next)
    {
        next = nullptr;
        return *this;
    }
    next = new Node(*other.next);
    return *this;
}

Value &Node::getValue()
{
    return value;
}

Key &Node::getKey()
{
    return key;
}

List::List(const List &b) 
{
    Node *current = b.first;
    while (current != nullptr)
    {
        this->push_back(current->key, current->value);
        current = current->next;
    }
}
List::List(List &&b) : first(std::move(b.first)), last(std::move(b.last)) 
{
    while (b.first != nullptr)
    {
        b.remove_first();
    }
}

List &List::operator=(const List &other)
{
    if (this == &other)
        return *this;
    while (first != nullptr)
    {
        remove_first();
    }
    Node *current = other.first;
    while (current != nullptr)
    {
        this->push_back(current->key, current->value);
        current = current->next;
    }
    return *this;
}

bool List::is_empty()
{
    return (first == nullptr);
}

bool List::push_back(const Key &name, const Value &data)
{
    Node *p = new Node(name, data);
    if (is_empty())
    {
        first = p;
        last = p;
        return true;
    }
    last->next = p;
    last = p;
    return true;
}

bool List::contains(const Key &name)
{
    Node *p = first;
    while (p != nullptr)
    {
        if (p->key == name)
            return true;
        p = p->next;
    }
    return false;
}

Node *List::getFirst()
{
    return first;
}

Node *List::find(const Key &name)
{
    Node *p = first;
    while (p != nullptr)
    {
        if (p->key == name)
            return p;
        p = p->next;
    }
    return nullptr;
}

void List::remove_first()
{
    if (is_empty())
        return;
    Node *p = first;
    first = p->next;
    delete p;
}

void List::remove_last()
{
    if (is_empty())
        return;
    if (first == last)
    {
        remove_first();
        return;
    }
    Node *p = first;
    while (p->next != last)
        p = p->next;
    p->next = nullptr;
    delete last;
    last = p;
}

bool List::remove(const Key &k)
{
    if (is_empty())
        return false;
    if (first->key == k)
    {
        remove_first();
        return true;
    }
    else if (last->key == k)
    {
        remove_last();
        return true;
    }
    Node *slow = first;
    Node *fast = first->next;
    while (fast && fast->key != k)
    {
        fast = fast->next;
        slow = slow->next;
    }
    if (fast == nullptr)
    {
        return false;
    }
    slow->next = fast->next;
    delete fast;
    return true;
}
