#include "List.hpp"
#include <iostream>

Value::Value(const Value &other) : age(other.age), weight(other.weight) {};

bool operator==(const Value &v1, const Value &v2) {
  if (v1.age != v2.age)
    return false;
  if (v1.weight != v2.weight)
    return false;
  return true;
}

bool operator!=(const Value &v1, const Value &v2) { return !(v1 == v2); }

List::List(const List &b) noexcept {
  Node *current = b.first;
  while (current) {
    pushBack(current->key, current->value);
    current = current->next;
  }
}

List::~List() { clear(); }

List &List::operator=(const List &other) noexcept {
  if (this == &other) {
    return *this;
  }
  clear();
  Node *current = other.first;
  while (current) {
    pushBack(current->key, current->value);
    current = current->next;
  }

  return *this;
}

void List::clear() {
  while (first != nullptr) {
    removeFirst();
  }
}

bool List::isEmpty() const { return first == nullptr; }

void List::pushBack(const Key &name, const Value &data) {
  Node *newNode = new Node(name, data);
  if (isEmpty()) {
    first = newNode;
    return;
  }

  Node *current = first;
  while (current->next) {
    current = current->next;
  }
  current->next = newNode;
}

bool List::contains(const Key &name) const {
  Node *p = first;
  while (p != nullptr) {
    if (p->key == name)
      return true;
    p = p->next;
  }
  return false;
}

const Value &List::findByKey(const Key &name) const {
  Node *p = first;
  while (p != nullptr) {
    if (p->key == name)
      return p->value;
    p = p->next;
  }
  throw std::runtime_error("key" + name + "found");
}

void List::removeFirst() {
  if (isEmpty())
    return;
  Node *p = first;
  first = p->next;
  delete p;
}

const Value &List::getFirstValue() const {
  if (isEmpty()) {
    throw std::runtime_error("list is empty");
  }
  return first->value;
}

const Key &List::getFirstKey() const {
  if (isEmpty()) {
    throw std::runtime_error("list is empty");
  }
  return first->key;
}

bool List::remove(const Key &k) {
  if (isEmpty())
    return false;

  if (first->key == k) {
    removeFirst();
    return true;
  }

  Node *slow = first;
  Node *fast = first->next;
  while (fast && fast->key != k) {
    fast = fast->next;
    slow = slow->next;
  }

  if (fast == nullptr)
    return false;

  slow->next = fast->next;
  delete fast;
  return true;
}
