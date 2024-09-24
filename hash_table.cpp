#include <iostream>
using namespace std;
typedef std::string Key;

struct Value
{
    unsigned age;
    unsigned weight;
    Value() : age(0), weight(0) {};
    Value(const unsigned &a, const unsigned &w) : age(a), weight(w) {};
    Value(const Value &other)
    {
        age = other.age;
        weight = other.weight;
    };
    ~Value() {};
};

struct Node
{
    Key key;
    Value value;
    Node *next;

    Node(const Key &name, const Value &data) : key(name), value(data), next(nullptr) {};
    Node() : key("no"), next(nullptr) {};
    Node(const Node &other)
    {
        key = other.key;
        Value value(other.value);
        if (other.next != nullptr) {
            next = new Node(*(other.next));
            
        }
    };
};

struct List
{
    Node *first;
    Node *last;

    List() : first(nullptr), last(nullptr) {};

    bool is_empty()
    {
        return (first == nullptr);
    }

    bool push_back(const Key &name, const Value &data)
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
    };

    bool contains(const Key &name)
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
    Node *find(const Key &name)
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

    void remove_first()
    {
        if (is_empty())
            return;
        Node *p = first;
        first = p->next;
        delete p;
    }

    void remove_last()
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

    bool remove(const Key &k)
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
};

int hashFunc(const Key &name, const size_t table_size)
{
    int hash = 0;
    size_t size = name.size();
    for (size_t i = 0; i < size; i++)
    {
        hash = (hash * 31 + name[i]) % table_size;
    }
    return hash;
}

class HashTable
{

    const size_t size = 191;
    List *arr;
    size_t curSize;

public:
    HashTable()
    {
        curSize = 0;
        arr = new List[size];
    };
    ~HashTable()
    {
        delete[] arr;
    };

    /*HashTable(const HashTable &b){
        arr = new List[size];
        curSize = b.curSize;
        for (size_t i = 0; i < size; i++) {
            if (!(b.arr[i].is_empty())) {
                this->arr[i].first
            }
        }
    }; // copy
    HashTable(HashTable &&b);
*/
    void swap(HashTable &b);

    HashTable &operator=(const HashTable &b);
    HashTable &operator=(HashTable &&b);

    // Очищает контейнер.
    void clear()
    {
        size_t i = 0;
        while (i < size)
        {
            if (!(arr[i].is_empty()))
            {
                while (arr[i].first != nullptr)
                {
                    arr[i].remove_first();
                }
            }

            i++;
        }
    };
    // Удаляет элемент по заданному ключу.
    bool erase(const Key &k)
    {
        size_t hash = hashFunc(k, this->size);
        size_t i = 0;
        List list = arr[hash];
        while (i < curSize)
        {
            if (arr[hash].is_empty())
                return false;

            if (arr[hash].remove(k))
                return true;
            i++;
        }
        return false;
    };

    bool insert(const Key &k, const Value &v)
    {
        size_t hash = hashFunc(k, this->size);
        if (!(arr[hash].find(k)))
        {
            arr[hash].push_back(k, v);
            curSize += 1;
            return true;
        }
        return false;
    };

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key &k) const
    {
        size_t hash = hashFunc(k, this->size);
        return arr[hash].contains(k);
    };

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнере, следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    Value &operator[](const Key &k)
    {
        size_t hash = hashFunc(k, this->size);
        Value v;
        insert(k, v);
        return (arr[hash].find(k)->value);
    };

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value &at(const Key &k);
    const Value &at(const Key &k) const;

    size_t sizen() const
    {
        return size;
    };

    bool empty() const
    {
        return (curSize == 0);
    };

    friend bool operator==(const HashTable &a, const HashTable &b){
        if (a.curSize != b.curSize)
            return false;
        for (size_t i = 0; i < a.size; i++) {
            if (a.arr[i].contains(b.arr[i].first->key))
                return true;
            
            for (size_t j = 0; j < b.curSize; j++) {
                while (b.arr[i]. != last)
                    p = p->next;
            }
        }
    };
    friend bool operator!=(const HashTable &a, const HashTable &b);
};

int main()
{
    HashTable table;
    std::cout << table.sizen();
    std::cout << table.empty();
    if (table.insert("Alice", Value(30, 150)))
    {
        std::cout << "Alice добавлена.\n";
    }
    else
    {
        std::cout << "Ошибка при добавлении Alice.\n";
    }

    if (table.insert("Bob", Value(25, 180)))
    {
        std::cout << "Bob добавлен.\n";
    }
    else
    {
        std::cout << "Ошибка при добавлении Bob.\n";
    }
    std::cout << table.sizen();
    std::cout << table.empty();
    if (table.insert("Charlie", Value(28, 165)))
    {
        std::cout << "Charlie добавлен.\n";
    }
    else
    {
        std::cout << "Ошибка при добавлении Charlie.\n";
    }


    if (!table.insert("Alice", Value(30, 150)))
    {
        std::cout << "Alice уже существует, не удалось добавить дубликат.\n";
    }
    std::cout << table["Alice"].age;
    std::cout << table["Anton"].age;

    if (table.erase("Bob"))
    {
        std::cout << "Bob удален.\n";
    }
    else
    {
        std::cout << "Ошибка при удалении Bob.\n";
    }
    if (table.contains("Alice"))
    {
        std::cout << "Alice есть.\n";
    }
    if (table.erase("Alice"))
    {
        std::cout << "Alice удалена.\n";
    }
    else
    {
        std::cout << "Ошибка при удалении Alice.\n";
    }
    if (!table.contains("Alice"))
    {
        std::cout << "Alice no.\n";
    }

    if (!table.erase("Dave"))
    {
        std::cout << "Dave не найден, не удалось удалить.\n";
    }

    if (table.erase("Charlie"))
    {
        std::cout << "Charlie удален.\n";
    }
    else
    {
        std::cout << "Ошибка при удалении Charlie.\n";
    }
    return 0;
}