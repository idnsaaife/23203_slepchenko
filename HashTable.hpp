#pragma once
#include "List.hpp"

class HashTable {
  static constexpr size_t INIT_CAPACITY = 2;
  static constexpr double MAX_LOAD_FACTOR = 0.75;
  size_t capacity = INIT_CAPACITY;
  size_t curAmount = 0;
  List *arr = nullptr;
  void rehash();

public:
  /*
  Constructs a new HashTable object with a default capacity
   */
  HashTable();
  /*
  Destructs the HashTable object
   */
  ~HashTable();
  /*
  Copy constructor
  Creates a deep copy of another HashTable object
  b  is the HashTable object to copy
  */
  HashTable(const HashTable &other);
  /*
  Move constructor
  Creates new HashTable object by moving another HashTable object to this one
  b is the HashTable to move
  */
  HashTable(HashTable &&other) noexcept;
  /*
  swap two HashTable objects
  */
  void swap(HashTable &other);
  /*
  assigns values to the container
  */
  HashTable &operator=(const HashTable &other);
  HashTable &operator=(HashTable &&other);
  /*
  clears the contents
  */
  void clear();
  /*
  erases elements by key
  returns true if element was in HashTable
  returns false if element wasn't in HashTable
  */
  bool erase(const Key &k);
  /*inserts elements
  returns true if element is new
  returns false if element with this key already added to HashTable
  */
  bool insert(const Key &k, const Value &v);
  /*
  checks if the container contains element with specific key
  */
  bool contains(const Key &k) const;
  /*
  returns a value by key,
  if container doesn't contain this value inserts the value created by default
  constructor and returns a reference to it
  */
  Value &operator[](const Key &k);
  /*
  returns a value by key, throws an exception(std::runtime_error) on failure
  */
  Value &at(const Key &k);
  const Value &at(const Key &k) const;
  /*
  returns capacity
  */
  size_t size() const;
  /*
  returns number of added elements
  */
  size_t amount() const;
  /*
  checks whether the container is empty
  */
  bool empty() const;
  /*
  compares the values in two HashTable objects
  */
  friend bool operator==(const HashTable &a, const HashTable &b);
  friend bool operator!=(const HashTable &a, const HashTable &b);
};
