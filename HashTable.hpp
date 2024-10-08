#include "List.hpp"
#include <iostream>


class HashTable
{
    static constexpr size_t capacity = 191;
    List *arr;
    size_t curAmount = 0;

public:
    /*
    Constructs a new HashTable object with a default capacity 191
     */
    HashTable();
    /*
    Destructs the HashTable object
     */
    ~HashTable();
    /*
    Copy constructor
    Creates a deep copy of another HashTable object
    b  The HashTable object to copy
    */
    HashTable(const HashTable &b);
    /*
    Move constructor
    Creates new HashTable object by moving another HashTable object to this one
    b The HashTable to move
    */
    HashTable(HashTable &&b);
    /*swap two HashTable objects*/
    void swap(HashTable &b);
    /*
    assigns values to the container
    */
    HashTable &operator=(const HashTable &b);
    /*
    clears the contents
    */
    void clear();
    /*erases elements by key*/
    bool erase(const Key &k);
    /*inserts elements 
    return true if element is new
    return false if element with this key already added to HashTable or */
    bool insert(const Key &k, const Value &v); 
    bool contains(const Key &k) const;
    Value &operator[](const Key &k);
    Value &at(const Key &k);
    const Value &at(const Key &k) const;
    size_t size() const;
    size_t amount() const; 
    bool empty() const; 
    friend bool operator==(const HashTable &a, const HashTable &b);
    friend bool operator!=(const HashTable &a, const HashTable &b);
};
