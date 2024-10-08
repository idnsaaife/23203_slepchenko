#include "HashTable.hpp"
#include "googletest/googletest/include/gtest/gtest.h"
#include <string>
#include <cstdlib>
#include <ctime>


TEST(HashTableTest, TestEmpty)
{
    HashTable ht;
    ASSERT_EQ(ht.HashTable::empty(), true);
}

TEST(HashTableTest, TestNotEmpty)
{
    HashTable ht;
    ht.HashTable::insert("Ann", Value(28, 165));
    ht.HashTable::insert("Alice", Value(25, 70));
    ASSERT_EQ(ht.HashTable::empty(), false);
}

TEST(HashTableTest, TestAmount)
{
    HashTable ht;
    ht.HashTable::insert("Ann", Value(28, 165));
    ht.HashTable::insert("Alice", Value(25, 70));
    ASSERT_EQ(ht.HashTable::amount() == 2, true);
}

TEST(HashTableTest, TestInsertDublicate)
{
    HashTable ht;
    ht.HashTable::insert("Alice", Value(25, 70));
    ASSERT_EQ(ht.HashTable::insert("Alice", Value(26, 70)), false);
}


TEST(HashTableTest, TestInsert)
{
    HashTable ht;
    ht.HashTable::insert("allicE", Value(25, 70));
    ht.HashTable::insert("DAshaaaaaaaaaaaan", Value(26, 75));
    ASSERT_EQ(ht["allicE"], Value(25, 70));
    ASSERT_EQ(ht["DAshaaaaaaaaaaaan"], Value(26, 75));
}

TEST(HashTableTest, TestContains)
{
    HashTable ht;
    Value v(25, 70);
    ht.HashTable::insert("Alice", v);
    ht.erase("Alice");
    ASSERT_EQ(ht.HashTable::contains("Alice"), false);
}

TEST(HashTableTest, TestFind)
{
    HashTable ht;
    Value v(25, 70);
    ht.HashTable::insert("Alice", v);
    ASSERT_EQ(ht["Alice"], v);
    ASSERT_EQ(ht["Ann"], Value());
    ASSERT_EQ(ht.at("Alice"), v);
    ASSERT_THROW(ht.at("All"), std::runtime_error);
}


TEST(HashTableTest, TestInsert1)
{
    HashTable ht;
    ht.HashTable::insert("Alice", Value(25, 70));
    ASSERT_EQ(ht.HashTable::insert("Alice", Value(26, 50)), false);
}

TEST(HashTableTest, TestInsert2)
{
    HashTable ht;
    ht.HashTable::insert("Alice", Value(25, 70));
    ASSERT_EQ(ht.HashTable::insert("Alice", Value(25, 70)), false);
}


TEST(HashTableTest, TestEmpty1)
{
    HashTable ht;
    ht.HashTable::insert("Charlie", Value(28, 165));
    ht.HashTable::erase("Charlie");
    ASSERT_EQ(ht.HashTable::empty(), true);
}

TEST(HashTableTest, TestErase)
{
    HashTable ht;
    ht.HashTable::insert("Charlie", Value(28, 165));
    ht.HashTable::insert("Chacha", Value(29, 166));
    ht.HashTable::erase("Charlie");
    ASSERT_EQ(ht.HashTable::erase("Charlie"), false);
}

TEST(HashTableTest, TestEraseIfNotInserted)
{
    HashTable ht;
    ht.HashTable::insert("Charlie", Value(28, 165));
    ASSERT_EQ(ht.HashTable::erase("Alice"), false);
}

TEST(HashTableTest, TestEraseIfEmpty)
{
    HashTable ht;
    ASSERT_EQ(ht.HashTable::erase("Alice"), false);
}

TEST(HashTableTest, TestHashFunc)
{
    HashTable ht;
    srand(time(NULL));
    const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
    for (size_t i = 0; i < (ht.HashTable::size() * 2); i++)
    {
        std ::string name;
        for (size_t j = 0; j < 15; j++)
        {
            name += alphabet[rand() % 15];
        }
        ht.HashTable::insert(name, Value(i, i));
    }
    ASSERT_EQ(ht.HashTable::amount() > ht.HashTable::size(), true);
}

TEST(HashTableTest, TestClear)
{
    HashTable ht;
    srand(time(NULL));
    const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
    for (size_t i = 0; i < (ht.HashTable::size() * 2); i++)
    {
        std ::string name;
        for (size_t j = 0; j < 10; j++)
        {
            name += alphabet[rand() % 10];
        }
        ht.HashTable::insert(name, Value(i, i));
    }
    ht.clear();
    ASSERT_EQ(ht.HashTable::empty(), true);
}

TEST(HashTableTest, TestClearEmpty)
{
    HashTable ht;
    ht.HashTable::clear();
    ASSERT_EQ(ht.HashTable::empty(), true);
}


TEST(HashTableTest, TestEqual)
{
    HashTable ht;
    ht.HashTable::insert("Alice", Value(5, 13));
    ht.HashTable::insert("Alena", Value(7, 10));
    ht.HashTable::insert("Charlie", Value(34, 130));
    HashTable ht1;
    ht1.HashTable::insert("Alice", Value(5, 13));
    ht1.HashTable::insert("Alena", Value(7, 10));
    ht1.HashTable::insert("Charlie", Value(34, 130));
    ASSERT_EQ(ht1 == ht, true);
}

TEST(HashTableTest, TestEqual1)
{
    HashTable ht;
    ht.HashTable::insert("Alice", Value(5, 13));
    ht.HashTable::insert("Alena", Value(7, 10));
    ht.HashTable::insert("Charlie", Value(34, 130));
    HashTable ht1;
    ht1.HashTable::insert("Alice", Value(5, 13));
    ht1.HashTable::insert("Alena", Value(7, 11));
    ht1.HashTable::insert("Charlie", Value(34, 130));
    ASSERT_EQ(ht1 == ht, false);
}

TEST(HashTableTest, TestCopy)
{
    HashTable ht;
    srand(time(NULL));
    const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
    for (size_t i = 0; i < (ht.HashTable::size() * 2); i++)
    {
        std ::string name;
        for (size_t j = 0; j < 10; j++)
        {
            name += alphabet[rand() % 10];
        }
        ht.HashTable::insert(name, Value(i, i));
    }
    HashTable ht1(ht);
    ASSERT_EQ(ht1 == ht, true);
}

TEST(HashTableTest, TestCopy1)
{
    HashTable ht;
    srand(time(NULL));
    const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
    for (size_t i = 0; i < (ht.HashTable::size() * 2); i++)
    {
        std ::string name;
        for (size_t j = 0; j < 10; j++)
        {
            name += alphabet[rand() % 10];
        }
        ht.HashTable::insert(name, Value(i, i));
    }
    HashTable ht1;
    ht1.HashTable::insert("Alice", Value(5, 6));
    ht1 = ht;
    ASSERT_EQ(ht1 == ht, true);
}

TEST(HashTableTest, TestCopy2)
{
    HashTable ht;
    srand(time(NULL));
    const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
    for (size_t i = 0; i < (ht.HashTable::size() * 2); i++)
    {
        std ::string name;
        for (size_t j = 0; j < 10; j++)
        {
            name += alphabet[rand() % 10];
        }
        ht.HashTable::insert(name, Value(i, i));
    }
    HashTable ht1;
    ht1.HashTable::insert("Alice", Value(5, 6));
    ht1 = ht;
    ASSERT_EQ(ht1.HashTable::contains("Alice"), false);
}

TEST(HashTableTest, TestCopy3)
{
    HashTable ht;
    ht.HashTable::insert("alice", Value(5, 56));
    ht.HashTable::insert("darya", Value(5, 57));
    ht = ht;
    ASSERT_EQ(ht.HashTable::contains("darya"), true);
}

TEST(HashTableTest, TestHash1) {
    HashTable ht;
    ht.HashTable::insert("acb", Value(5, 13));
    ht.HashTable::insert("abcabc", Value(8, 7));
    ASSERT_EQ(ht.HashTable::contains("acb") && ht.HashTable::contains("abcabc"), true);
}

TEST(HashTableTest, TestSwap)
{
    HashTable ht;
    ht.HashTable::insert("Alice", Value(5, 13));
    HashTable ht1;
    ht1.HashTable::insert("Ann", Value(6, 73));
    ht.HashTable::swap(ht1);
    ASSERT_EQ(ht.HashTable::contains("Ann") && (ht1.HashTable::contains("Alice")), true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
