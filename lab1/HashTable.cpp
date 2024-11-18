#include "HashTable.hpp"
#include "List.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

static constexpr size_t HASH_KEY = 31;

namespace
{
    size_t hashFunc(const Key &name, const size_t table_size)
    {
        size_t hash = 0;
        const size_t size = name.size();
        for (size_t i = 0; i < size; i++)
        {
            hash = (hash * HASH_KEY + name[i]) % table_size;
        }
        return hash;
    }
} // namespace

HashTable::HashTable() : arr(new List[capacity]) {};

HashTable::~HashTable() { delete[] arr; }

HashTable::HashTable(const HashTable &other)
    : capacity(other.capacity), curAmount(other.curAmount),
      arr(new List[capacity])
{
    std::copy(other.arr, other.arr + capacity, arr);
}

HashTable::HashTable(HashTable &&other) noexcept
    : capacity(other.capacity), curAmount(other.curAmount), arr(other.arr)
{
    other.arr = nullptr;
    other.curAmount = 0;
    other.capacity = INIT_CAPACITY;
}

void HashTable::swap(HashTable &other) noexcept
{
    std::swap(capacity, other.capacity);
    std::swap(curAmount, other.curAmount);
    std::swap(arr, other.arr);
}

HashTable &HashTable::operator=(const HashTable &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete[] arr;
    curAmount = other.curAmount;
    capacity = other.capacity;
    arr = new List[other.capacity];
    std::copy(other.arr, other.arr + capacity, arr);
    return *this;
}

HashTable &HashTable::operator=(HashTable &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    delete[] arr;
    curAmount = other.curAmount;
    capacity = other.capacity;
    arr = other.arr;
    other.arr = nullptr;
    other.curAmount = 0;
    other.capacity = 0;
    return *this;
}

void HashTable::clear()
{
    size_t i = 0;
    while (i < capacity)
    {
        arr[i].clear();
        i++;
    }
    curAmount = 0;
    capacity = INIT_CAPACITY;
}

bool HashTable::erase(const Key &k)
{
    const size_t hash = hashFunc(k, capacity);

    if (!arr[hash].remove(k))
    {
        return false;
    }

    curAmount--;
    return true;
}

void HashTable::rehash()
{
    const size_t old_capacity = capacity;
    capacity *= CAPACITY_RATE; //?????????
    List *newArr = new List[capacity];
    for (size_t i = 0; i < old_capacity; i++)
    {
        while (!arr[i].isEmpty())
        {
            const size_t newHash = hashFunc(arr[i].getFirstKey(), capacity);
            newArr[newHash].pushBack(arr[i].getFirstKey(), arr[i].getFirstValue()); // push node
            arr[i].removeFirst();
        }
    }
    delete[] arr;
    arr = newArr;
}

bool HashTable::insert(const Key &k, const Value &v)
{
    if (static_cast<double>(curAmount) >= static_cast<double>(capacity) * MAX_LOAD_FACTOR)
    {
        rehash();
    }
    const size_t hash = hashFunc(k, capacity);
    if (arr[hash].contains(k))
    {
        return false;
    }
    arr[hash].pushBack(k, v);
    curAmount += 1;
    return true;
}

[[nodiscard]] bool HashTable::contains(const Key &k) const
{
    const size_t hash = hashFunc(k, capacity);
    return arr[hash].contains(k);
}

Value &HashTable::operator[](const Key &k)
{
    const size_t hash = hashFunc(k, capacity);
    if (arr[hash].contains(k))
    {
        return const_cast<Value &>(arr[hash].findByKey(k));
    }
    insert(k, {});
    return const_cast<Value &>(arr[hashFunc(k, capacity)].findByKey(k));
}

[[nodiscard]] const Value &HashTable::at(const Key &k) const
{
    const size_t hash = hashFunc(k, capacity);
    if (arr[hash].contains(k))
    {
        return (arr[hash].findByKey(k));
    }
    throw std::runtime_error("key " + k + " doesn't exist");
}

Value &HashTable::at(const Key &k)
{
    return const_cast<Value &>(static_cast<const HashTable &>(*this).at(k));
}

[[nodiscard]] size_t HashTable::size() const { return capacity; }

[[nodiscard]] size_t HashTable::amount() const { return curAmount; }

[[nodiscard]] bool HashTable::empty() const { return (curAmount == 0); }

bool operator==(const HashTable &a, const HashTable &b)
{
    if (a.curAmount != b.curAmount)
    {
        return false;
    }
    for (size_t i = 0; i < a.capacity; i++)
    {
        List tempA(a.arr[i]);
        while (!tempA.isEmpty())
        {
            if (!b.contains(tempA.getFirstKey()))
            {
                return false;
            }
            if (b.at(tempA.getFirstKey()) != tempA.getFirstValue())
            {
                return false;
            }
            tempA.removeFirst();
        }
    }
    return true;
}

bool operator!=(const HashTable &a, const HashTable &b) { return !(a == b); }
