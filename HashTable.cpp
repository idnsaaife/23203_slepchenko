#include "HashTable.hpp"
#include <iostream>

static int hashFunc(const Key &name, const size_t table_size)
{
    int hash = 0;
    size_t size = name.size();
    for (size_t i = 0; i < size; i++)
    {
        hash = (hash * 31 + name[i]) % table_size;
    }
    return hash;
}

HashTable::HashTable()
{
    arr = new List[capacity];
}

HashTable::~HashTable()
{
    for (size_t i = 0; i < capacity; i++)
    {
        while (arr[i].first != nullptr)
        {
            arr[i].List::remove_first();
        }
    }
    delete[] arr;
}

HashTable::HashTable(const HashTable &b) : arr(new List[b.capacity]), curAmount(b.curAmount)
{
    for (size_t i = 0; i < b.capacity; i++)
    {
        arr[i] = b.arr[i];
    }
}

HashTable::HashTable(HashTable &&b) : arr(b.arr), curAmount(b.curAmount)
{

    b.arr = nullptr;
    b.curAmount = 0;
}

void HashTable::swap(HashTable &b)
{
    HashTable temp(*this);
    *this = b;
    b = temp;
}

HashTable &HashTable::operator=(const HashTable &b)
{
    if (this == &b)
        return *this;
    delete[] arr;
    curAmount = b.curAmount;
    arr = new List[b.capacity];
    for (size_t i = 0; i < b.capacity; i++)
    {
        arr[i] = b.arr[i];
    }
    return *this;
}


void HashTable::clear()
{
    size_t i = 0;
    while (i < capacity)
    {
        if (!(arr[i].is_empty()))
        {
            while (arr[i].first != nullptr)
            {
                arr[i].List::remove_first();
            }
        }
        i++;
    }
    curAmount = 0;
};

bool HashTable::erase(const Key &k)
{
    size_t hash = hashFunc(k, this->capacity);
    size_t i = 0;
    List list = arr[hash];
    while (i < curAmount)
    {
        if (arr[hash].List::is_empty())
            return false;

        if (arr[hash].List::remove(k))
        {
            curAmount--;
            return true;
        }
        i++;
    }

    return false;
};

bool HashTable::insert(const Key &k, const Value &v)
{
    size_t hash = hashFunc(k, this->capacity);
    Node *temp = arr[hash].List::find(k);
    if ((nullptr != temp) && (v != temp->Node::getValue()))
    {
        return false;
    }
    if (nullptr != temp && v == temp->Node::getValue())
    {
        return false;
    }
    arr[hash].List::push_back(k, v);
    curAmount += 1;
    return true;
};

bool HashTable::contains(const Key &k) const
{
    size_t hash = hashFunc(k, this->capacity);
    return arr[hash].List::contains(k);
};

Value &HashTable::operator[](const Key &k)
{
    size_t hash = hashFunc(k, this->capacity);
    Value v;
    insert(k, v);
    return (arr[hash].List::find(k)->Node::getValue());
};

Value &HashTable::at(const Key &k)
{
    size_t hash = hashFunc(k, this->capacity);
    Node *place = arr[hash].List::find(k);
    if (place == nullptr)
        throw std::runtime_error("key" + k + "doesn't exist");
    return place->Node::getValue();
};

const Value &HashTable::at(const Key &k) const
{
    size_t hash = hashFunc(k, this->capacity);
    Node *place = arr[hash].find(k);
    if (place == nullptr)
        throw std::runtime_error("key" + k + "doesn't exist");
    return place->getValue();
}

size_t HashTable::size() const
{
    return capacity;
};

size_t HashTable::amount() const
{
    return curAmount;
};

bool HashTable::empty() const
{
    return (curAmount == 0);
};

bool operator==(const HashTable &a, const HashTable &b)
{
    bool flag = false;
    for (size_t i = 0; i < a.capacity; i++)
    {
        Node* tempA = a.arr[i].first;
        while (nullptr != tempA)
        {
            for (size_t j = 0; j < b.capacity; j++)
            {
                Node *tempB = b.arr[j].find(tempA->getKey());
                if (nullptr != tempB && tempB->getValue() == tempA->getValue())
                {
                    flag = true;
                    break;
                }
            }
            if (false == flag)
            {
                return false;
            }
            flag = false;
            tempA = tempA->next;
        }
    }
    for (size_t i = 0; i < b.capacity; i++)
    {
        Node *tempB = b.arr[i].first;
        while (nullptr != tempB)
        {
            for (size_t j = 0; j < a.capacity; j++)
            {
                Node *tempA = a.arr[j].find(tempB->getKey());
                if (nullptr != tempA && tempA->getValue() == tempB->getValue())
                {
                    flag = true;
                    break;
                }
            }
            if (false == flag)
            {
                return false;
            }
            flag = false;
            tempB = tempB->next;
        }
    }
    return true;
};

bool operator!=(const HashTable &a, const HashTable &b)
{
    return !(a == b);
};
