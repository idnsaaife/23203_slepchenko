#pragma once
#include <iostream>

using Key = std::string;

class Value {
public:
  Value(const unsigned &a, const unsigned &w) : age(a), weight(w) {};
  Value(const Value &other);
  Value() = default;
  ~Value() = default;
  friend bool operator==(const Value &v1, const Value &v2);
  friend bool operator!=(const Value &v1, const Value &v2);

private:
  unsigned age = 0;
  unsigned weight = 0;
};

class List {
private:
  struct Node {
    Node(const Key &name, const Value &data) : key(name), value(data) {}
    Node(const Node &other) = delete;
    Node(Node &&other) = delete;
    Node &operator=(const Node &other) = delete;
    Node &operator=(Node &&other) = delete;
    Key key;
    Value value;
    Node *next = nullptr;
  };
  Node *first = nullptr;

public:
  List() = default;
  ~List();
  List(const List &b) noexcept;
  List(List &&b) = delete;

  List &operator=(const List &other) noexcept;
  List &operator=(List &&other) = delete;

  void pushBack(const Key &name, const Value &data);
  bool contains(const Key &name) const;
  void clear();
  bool isEmpty() const;
  const Value &findByKey(const Key &name) const;
  const Key &getFirstKey() const;
  const Value &getFirstValue() const;
  void removeFirst();
  bool remove(const Key &k);
};
