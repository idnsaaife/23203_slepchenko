#include "HashTable.hpp"
#include "gtest/gtest.h"
#include <string>
#include <fstream>

TEST(HashTableTest, TestEmpty)
{
    HashTable ht;
    EXPECT_TRUE(ht.empty());
    EXPECT_TRUE(ht.empty());
    EXPECT_TRUE(ht.empty());
    ht.insert("Emma", Value(12, 34));
    EXPECT_FALSE(ht.empty());
    EXPECT_FALSE(ht.empty());
    ht.clear();
    EXPECT_TRUE(ht.empty());

    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;

    HashTable ht1;
    ht1.insert("Emma", Value(12, 34));
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.insert(name, Value()));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_FALSE(ht1.empty());
    EXPECT_FALSE(ht1.empty());
    EXPECT_TRUE(ht1.amount() > 1);
    EXPECT_TRUE(ht1.erase("Emma"));
    EXPECT_FALSE(ht1.empty());
    EXPECT_FALSE(ht1.empty());
    EXPECT_FALSE(ht1.empty());
    ht1.clear();
    EXPECT_TRUE(ht1.empty());
    EXPECT_TRUE(ht1.empty());
    EXPECT_TRUE(ht1.empty());

    HashTable ht2;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht2.insert(name, Value()));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);

    EXPECT_FALSE(ht2.empty());
    EXPECT_FALSE(ht2.empty());
    while (std::getline(Keys, name))
    {
        EXPECT_FALSE(ht2.empty());
        EXPECT_TRUE(ht2.erase(name));
    }
    EXPECT_TRUE(ht2.empty());
    EXPECT_TRUE(ht2.empty());

    ht2.clear();
    EXPECT_TRUE(ht2.empty());
    EXPECT_TRUE(ht2.empty());

    Keys.close();
}

TEST(HashTableTest, TestContains)
{
    HashTable ht;
    ht.insert("Emma", Value(9, 12));

    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.insert(name, Value()));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.contains(name));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    ht.erase("Emma");
    EXPECT_FALSE(ht.contains("Emma"));
    while (std::getline(Keys, name))
    {
        EXPECT_FALSE(ht.contains(name + "abc"));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    ht.clear();
    while (std::getline(Keys, name))
    {
        EXPECT_FALSE(ht.contains(name));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    HashTable ht1;
    EXPECT_FALSE(ht1.contains("Ann"));
    EXPECT_FALSE(ht1.contains("Annwwnn"));
    EXPECT_FALSE(ht1.contains("Annwweenn"));
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.insert(name, Value()));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.erase(name));
        EXPECT_FALSE(ht1.contains(name));
    }
    Keys.close();
}

TEST(HashTableTest, TestSizeAmount)
{
    HashTable ht;
    EXPECT_EQ(ht.size(), 2);
    EXPECT_EQ(ht.amount(), 0);
    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.insert(name, Value()));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_EQ(ht.amount(), 2000);
    size_t curAmount = ht.amount();
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.erase(name));
        size_t newCurAmount = ht.amount();
        EXPECT_EQ(curAmount - newCurAmount, 1);
        curAmount = newCurAmount;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_TRUE((ht.size() > 8));
    HashTable ht1;
    EXPECT_EQ(ht1.size(), 2);
    EXPECT_EQ(ht1.amount(), 0);
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.insert(name, Value()));
    }
    ht1.clear();
    EXPECT_EQ(ht1.size(), 2);
    EXPECT_EQ(ht1.amount(), 0);
    Keys.close();
}

TEST(HashTableTest, TestInsert)
{
    HashTable ht;
    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;
    size_t curAmount = ht.amount();
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.insert(name, Value()));
        size_t newCurAmount = ht.amount();
        EXPECT_EQ(newCurAmount - curAmount, 1);
        curAmount = newCurAmount;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    while (std::getline(Keys, name))
    {
        EXPECT_FALSE(ht.insert(name, Value()));
        size_t newCurAmount = ht.amount();
        EXPECT_EQ(newCurAmount, curAmount);
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_TRUE(ht.insert("Elle", Value(56, 12)));
    EXPECT_TRUE(ht.insert("Ellaae", Value(56, 12)));
    HashTable ht1;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.insert(name, Value()));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.erase(name));
        EXPECT_TRUE(ht1.insert(name, Value()));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    ht1.clear();
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.insert(name, Value()));
    }
    Keys.close();
}

TEST(HashTableTest, TestErase)
{
    HashTable ht;
    EXPECT_FALSE(ht.erase("abc"));
    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;
    size_t curAmount = ht.amount();
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.insert(name, Value()));
        size_t newCurAmount = ht.amount();
        EXPECT_EQ(newCurAmount - curAmount, 1);
        curAmount = newCurAmount;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.erase(name));
        EXPECT_FALSE(ht.erase(name + "abc"));
        size_t newCurAmount = ht.amount();
        EXPECT_EQ(curAmount - newCurAmount, 1);
        curAmount = newCurAmount;
    }
    EXPECT_TRUE(ht.empty());
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    while (std::getline(Keys, name))
    {
        EXPECT_FALSE(ht.erase(name));
        size_t newCurAmount = ht.amount();
        EXPECT_EQ(curAmount, newCurAmount);
    }

    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    HashTable ht1;
    while (std::getline(Keys, name))
    {
        EXPECT_FALSE(ht.erase(name));
        size_t newCurAmount = ht.amount();
        EXPECT_EQ(curAmount, newCurAmount);
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.insert(name, Value()));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    ht1.clear();
    while (std::getline(Keys, name))
    {
        EXPECT_FALSE(ht1.erase(name));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    Keys.close();
}

TEST(HashTableTest, TestClear)
{
    HashTable ht;
    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;
    size_t curAmount = ht.amount();
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.insert(name, Value()));
        size_t newCurAmount = ht.amount();
        EXPECT_EQ(newCurAmount - curAmount, 1);
        curAmount = newCurAmount;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    ht.clear();
    EXPECT_EQ(ht.amount(), 0);
    EXPECT_EQ(ht.size(), 2);
    while (std::getline(Keys, name))
    {
        EXPECT_FALSE(ht.contains(name));
        size_t newCurAmount = ht.amount();
        EXPECT_EQ(newCurAmount, 0);
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    ht.clear();
    EXPECT_EQ(ht.amount(), 0);
    EXPECT_EQ(ht.size(), 2);
    while (std::getline(Keys, name))
    {
        EXPECT_FALSE(ht.contains(name));
        size_t newCurAmount = ht.amount();
        EXPECT_EQ(newCurAmount, 0);
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    HashTable ht1;
    ht1.clear();
    EXPECT_TRUE(ht == ht1);
    EXPECT_EQ(ht1.amount(), 0);
    EXPECT_EQ(ht1.size(), 2);
    curAmount = ht1.amount();
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.insert(name, Value()));
        size_t newCurAmount = ht1.amount();
        EXPECT_EQ(newCurAmount - curAmount, 1);
        curAmount = newCurAmount;
    }
    EXPECT_TRUE(ht != ht1);
    ht1.clear();
    EXPECT_TRUE(ht == ht1);
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    Keys.close();
}

TEST(HashTableTest, TestAt)
{
    HashTable ht;
    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;
    size_t i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.insert(name, Value(i, i)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_EQ(ht[name], Value(i, i));
        EXPECT_EQ(ht.at(name), Value(i, i));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    while (std::getline(Keys, name))
    {
        EXPECT_EQ(ht[name + "abc"], Value());
        EXPECT_THROW(ht.at(name + "babc"), std::runtime_error);
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    HashTable ht1;
    while (std::getline(Keys, name))
    {
        EXPECT_EQ(ht1[name], Value());
        EXPECT_THROW(ht1.at(name + "a"), std::runtime_error);
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    Keys.close();
}

TEST(HashTableTest, TestEq)
{
    HashTable ht;
    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;
    size_t i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.insert(name, Value(i, i)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    HashTable ht1;
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.insert(name, Value(i, i)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_TRUE(ht1 == ht);
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.erase(name));
        EXPECT_TRUE(ht1 != ht);
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);

    HashTable ht2;
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht2.insert(name, Value(i, i * 10)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_TRUE(ht1 != ht2);
    HashTable ht3;
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht3.insert(name, Value(i + 1, i)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_TRUE(ht1 != ht3);
    HashTable ht4;
    ht4.insert("Alice", Value(5, 13));
    ht4.insert("Elle", Value(1, 1));
    ht4.insert("Charlie", Value(34, 130));
    EXPECT_TRUE(ht1 != ht4);
    HashTable ht5;
    EXPECT_TRUE(ht5 != ht1);
    EXPECT_TRUE(ht5 == ht);
    EXPECT_TRUE(ht5 == ht);
    Keys.close();
}

TEST(HashTableTest, TestMoveConstructor)
{
    HashTable ht;
    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;
    size_t i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.insert(name, Value(i, i)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    HashTable ht1(std::move(ht));
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.contains(name));
        EXPECT_EQ(ht1.at(name), Value(i, i));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    ht1.insert("Serena", Value(28, 75));
    EXPECT_TRUE(ht1.contains("Serena"));
    EXPECT_EQ(ht1.at("Serena"), Value(28, 75));
    HashTable ht2;
    HashTable ht3(std::move(ht2));
    EXPECT_TRUE(ht3.empty());
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht3.insert(name, Value(i, i)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_FALSE(ht3.empty());
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht3.contains(name));
        EXPECT_EQ(ht3.at(name), Value(i, i));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    HashTable ht4(std::move(ht1));
    HashTable ht5(std::move(ht3));
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht4.contains(name));
        EXPECT_EQ(ht4.at(name), Value(i, i));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht5.contains(name));
        EXPECT_EQ(ht5.at(name), Value(i, i));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    Keys.close();
}

TEST(HashTableTest, TestCopyConstructor)
{
    HashTable ht;
    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;
    size_t i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.insert(name, Value(i, i)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    HashTable ht1(ht);
    EXPECT_TRUE(ht == ht1);
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.contains(name));
        EXPECT_EQ(ht1.at(name), Value(i, i));
        EXPECT_TRUE(ht.contains(name));
        EXPECT_EQ(ht.at(name), Value(i, i));
        EXPECT_TRUE(ht1.insert(name + "a", Value(i, i)));
        EXPECT_FALSE(ht.contains(name + "a"));
        EXPECT_TRUE(ht1.contains(name + "a"));
        EXPECT_TRUE(ht.insert(name + "b", Value(i, i)));
        EXPECT_FALSE(ht1.contains(name + "b"));
        EXPECT_TRUE(ht.contains(name + "b"));
        EXPECT_EQ(ht1.at(name + "a"), Value(i, i));
        EXPECT_EQ(ht.at(name + "b"), Value(i, i));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_TRUE(ht != ht1);
    HashTable ht2;
    HashTable ht3(ht2);
    EXPECT_TRUE(ht3.empty());
    EXPECT_TRUE(ht2.empty());
    EXPECT_TRUE(ht2 == ht3);
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht3.insert(name, Value(i, i)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_FALSE(ht3.empty());
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht3.contains(name));
        EXPECT_EQ(ht3.at(name), Value(i, i));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_FALSE(ht3.empty());
    EXPECT_TRUE(ht2.empty());
    Keys.close();
}

TEST(HashTableTest, TestCopyAssignment)
{
    HashTable ht;
    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;
    size_t i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.insert(name, Value(i, i)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    ht = ht;
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.contains(name));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    HashTable ht1;
    ht1 = ht;
    EXPECT_TRUE(ht == ht1);
    ht1.insert("Name", Value(8, 9));
    EXPECT_FALSE(ht.contains("Name"));
    EXPECT_TRUE(ht1.contains("Name"));
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.contains(name));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    HashTable ht2;
    i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht2.insert(name + "bc", Value(i * 10, i * 10)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    ht = ht2;
    EXPECT_TRUE(ht == ht2);
    EXPECT_EQ(ht.amount(), ht2.amount());
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.contains(name + "bc"));
    }
    HashTable ht4;
    ht = ht4;
    EXPECT_TRUE(ht4 == ht);
    EXPECT_TRUE(ht.empty());
    EXPECT_TRUE(ht4.empty());
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    HashTable ht5;
    ht5.insert("Alice", Value(5, 13));
    ht5.insert("Alena", Value(7, 10));
    ht5.insert("Charlie", Value(34, 130));
    ht5.insert("Elle", Value(1, 1));
    ht5.insert("Ann", Value(5, 13));
    ht5.insert("Kate", Value(7, 10));
    ht5.insert("Alex", Value(34, 130));
    ht5.insert("Jenny", Value(1, 1));
    ht5.insert("Chuck", Value(5, 13));
    ht5.insert("Den", Value(7, 10));
    ht5.insert("Nate", Value(34, 130));
    ht5.insert("Blair", Value(1, 1));
    ht2 = ht5;
    EXPECT_TRUE(ht2 == ht5);
    EXPECT_EQ(ht2.amount(), ht5.amount());
    EXPECT_EQ(ht2.size(), ht5.size());
    Keys.close();
}

TEST(HashTableTest, TestMoveAssignment)
{
    HashTable ht;
    std::ifstream Keys("/Users/sofya/test/lab1/Keys.txt");
    std::string name;
    size_t i = 0;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht.insert(name, Value(i, i)));
        i++;
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);

    HashTable ht1;
    ht1 = std::move(ht);
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht1.contains(name));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    ht1.insert("Serena", Value(28, 75));
    EXPECT_TRUE(ht1.contains("Serena"));
    EXPECT_EQ(ht1.at("Serena"), Value(28, 75));

    HashTable ht2;
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht2.insert(name + "abcd", Value()));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    ht2 = std::move(ht1);
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht2.contains(name));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);
    EXPECT_TRUE(ht2.insert("Emma", Value(29, 75)));
    EXPECT_TRUE(ht2.contains("Emma"));
    EXPECT_EQ(ht2.at("Emma"), Value(29, 75));

    HashTable ht3;
    ht3 = std::move(ht2);
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht3.contains(name));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);

    ht3 = std::move(ht3);
    while (std::getline(Keys, name))
    {
        EXPECT_TRUE(ht3.contains(name));
    }
    Keys.clear();
    Keys.seekg(0, std::ios::beg);

    HashTable ht4;
    ht3 = std::move(ht4);
    EXPECT_TRUE(ht3.empty());
    Keys.close();
}

TEST(HashTableTest, TestSwap)
{

    HashTable ht;
    ht.insert("Alice", Value(5, 13));
    ht.insert("Alena", Value(7, 10));
    ht.insert("Charlie", Value(34, 130));
    ht.insert("Elle", Value(1, 1));
    ht.insert("Ann", Value(5, 13));
    ht.insert("Kate", Value(7, 10));
    ht.insert("Alex", Value(34, 130));
    ht.insert("Jenny", Value(1, 1));
    ht.insert("Chuck", Value(5, 13));
    ht.insert("Den", Value(7, 10));
    ht.insert("Nate", Value(34, 130));
    ht.insert("Blair", Value(1, 1));

    HashTable ht1;
    ht1.insert("Name1", Value(1, 1));
    ht1.insert("Name2", Value(1, 1));
    ht1.insert("Name3", Value(1, 1));
    ht1.insert("Name4", Value(1, 1));
    ht1.insert("Name5", Value(1, 1));
    ht1.insert("Name6", Value(1, 1));
    ht1.insert("Name7", Value(1, 1));
    ht1.insert("Name8", Value(1, 1));
    ht1.insert("Name9", Value(1, 1));
    ht1.insert("Name10", Value(1, 1));
    ht1.insert("Name11", Value(1, 1));
    ht1.insert("Name12", Value(1, 1));
    ht1.insert("Name13", Value(1, 1));
    ht1.insert("Name14", Value(1, 1));
    ht1.insert("Name15", Value(1, 1));
    ht1.insert("Name16", Value(1, 1));

    ht1.swap(ht);
    EXPECT_TRUE(ht1.contains("Alice"));
    EXPECT_TRUE(ht1.contains("Alena"));
    EXPECT_TRUE(ht1.contains("Charlie"));
    EXPECT_TRUE(ht1.contains("Elle"));
    EXPECT_TRUE(ht1.contains("Ann"));
    EXPECT_TRUE(ht1.contains("Kate"));
    EXPECT_TRUE(ht1.contains("Alex"));
    EXPECT_TRUE(ht1.contains("Jenny"));
    EXPECT_TRUE(ht1.contains("Chuck"));
    EXPECT_TRUE(ht1.contains("Den"));
    EXPECT_TRUE(ht1.contains("Nate"));
    EXPECT_TRUE(ht1.contains("Blair"));
    EXPECT_FALSE(ht1.contains("Name1"));
    EXPECT_FALSE(ht1.contains("Name2"));
    EXPECT_FALSE(ht1.contains("Name3"));
    EXPECT_FALSE(ht1.contains("Name4"));
    EXPECT_FALSE(ht1.contains("Name5"));
    EXPECT_FALSE(ht1.contains("Name6"));
    EXPECT_FALSE(ht1.contains("Name7"));
    EXPECT_FALSE(ht1.contains("Name8"));
    EXPECT_FALSE(ht1.contains("Name9"));
    EXPECT_FALSE(ht1.contains("Name10"));
    EXPECT_FALSE(ht1.contains("Name11"));
    EXPECT_FALSE(ht1.contains("Name12"));
    EXPECT_FALSE(ht1.contains("Name13"));
    EXPECT_FALSE(ht1.contains("Name14"));
    EXPECT_FALSE(ht1.contains("Name15"));
    EXPECT_FALSE(ht1.contains("Name16"));
    EXPECT_EQ(ht1.at("Alice"), Value(5, 13));
    ht1.insert("Serena", Value(28, 75));
    EXPECT_TRUE(ht1.contains("Serena"));
    EXPECT_FALSE(ht.contains("Serena"));
    EXPECT_EQ(ht1.at("Serena"), Value(28, 75));

    EXPECT_TRUE(ht.contains("Name1"));
    EXPECT_TRUE(ht.contains("Name2"));
    EXPECT_TRUE(ht.contains("Name3"));
    EXPECT_TRUE(ht.contains("Name4"));
    EXPECT_TRUE(ht.contains("Name5"));
    EXPECT_TRUE(ht.contains("Name6"));
    EXPECT_TRUE(ht.contains("Name7"));
    EXPECT_TRUE(ht.contains("Name8"));
    EXPECT_TRUE(ht.contains("Name9"));
    EXPECT_TRUE(ht.contains("Name10"));
    EXPECT_TRUE(ht.contains("Name11"));
    EXPECT_TRUE(ht.contains("Name12"));
    EXPECT_TRUE(ht.contains("Name13"));
    EXPECT_TRUE(ht.contains("Name14"));
    EXPECT_TRUE(ht.contains("Name15"));
    EXPECT_TRUE(ht.contains("Name16"));
    EXPECT_FALSE(ht.contains("Alice"));
    EXPECT_FALSE(ht.contains("Alena"));
    EXPECT_FALSE(ht.contains("Charlie"));
    EXPECT_FALSE(ht.contains("Elle"));
    EXPECT_FALSE(ht.contains("Ann"));
    EXPECT_FALSE(ht.contains("Kate"));
    EXPECT_FALSE(ht.contains("Alex"));
    EXPECT_FALSE(ht.contains("Jenny"));
    EXPECT_FALSE(ht.contains("Chuck"));
    EXPECT_FALSE(ht.contains("Den"));
    EXPECT_FALSE(ht.contains("Nate"));
    EXPECT_FALSE(ht.contains("Blair"));
    EXPECT_EQ(ht.at("Name3"), Value(1, 1));
    ht.insert("Serena", Value(28, 75));
    EXPECT_TRUE(ht.contains("Serena"));
    EXPECT_EQ(ht.at("Serena"), Value(28, 75));

    HashTable ht2;
    ht1.swap(ht2);
    EXPECT_TRUE(ht1.empty());
    EXPECT_TRUE(ht2.contains("Alice"));
    EXPECT_TRUE(ht2.contains("Alena"));
    EXPECT_TRUE(ht2.contains("Charlie"));
    EXPECT_TRUE(ht2.contains("Elle"));
    EXPECT_TRUE(ht2.contains("Ann"));
    EXPECT_TRUE(ht2.contains("Kate"));
    EXPECT_TRUE(ht2.contains("Alex"));
    EXPECT_TRUE(ht2.contains("Jenny"));
    EXPECT_TRUE(ht2.contains("Chuck"));
    EXPECT_TRUE(ht2.contains("Den"));
    EXPECT_TRUE(ht2.contains("Nate"));
    EXPECT_TRUE(ht2.contains("Blair"));

    ht.swap(ht);
    EXPECT_TRUE(ht.contains("Name1"));
    EXPECT_TRUE(ht.contains("Name2"));
    EXPECT_TRUE(ht.contains("Name3"));
    EXPECT_TRUE(ht.contains("Name4"));
    EXPECT_TRUE(ht.contains("Name5"));
    EXPECT_TRUE(ht.contains("Name6"));
    EXPECT_TRUE(ht.contains("Name7"));
    EXPECT_TRUE(ht.contains("Name8"));
    EXPECT_TRUE(ht.contains("Name9"));
    EXPECT_TRUE(ht.contains("Name10"));
    EXPECT_TRUE(ht.contains("Name11"));
    EXPECT_TRUE(ht.contains("Name12"));
    EXPECT_TRUE(ht.contains("Name13"));
    EXPECT_TRUE(ht.contains("Name14"));
    EXPECT_TRUE(ht.contains("Name15"));
    EXPECT_TRUE(ht.contains("Name16"));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
