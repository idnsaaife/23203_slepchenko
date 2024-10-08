#include <iostream>

typedef std::string Key;

struct Value
{
public:
    Value(const unsigned &a, const unsigned &w) : age(a), weight(w) {};
    Value(const Value &other);
    Value() {};
    ~Value() {};
    friend bool operator==(const Value &v1, const Value &v2);
    friend bool operator!=(const Value &v1, const Value &v2);
    unsigned age = 0;
    unsigned weight = 0;
};

struct Node
{
public:
    Node(const Key &name, const Value &data) : key(name), value(data), next(nullptr) {};
    Node() : key(" "), next(nullptr) {};
    Node(const Node &other);
    Node(Node &&other);
    Node &operator=(const Node &other);
    Value &getValue();
    Key &getKey();
    Key key;
    Value value;
    Node *next;
};

struct List
{
    Node *first;
    Node *last;
    List() : first(nullptr), last(nullptr) {};
    List(const List &b);
    List(List &&b);
    List &operator=(const List &other);
    bool is_empty();

    bool push_back(const Key &name, const Value &data);
    bool contains(const Key &name);
    Node *getFirst();
    Node *find(const Key &name);
    void remove_first();
    void remove_last();
    bool remove(const Key &k);
};
