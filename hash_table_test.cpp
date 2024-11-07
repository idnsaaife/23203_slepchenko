#include "HashTable.hpp"
#include "googletest/googletest/include/gtest/gtest.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

TEST(HashTableTest, TestEmpty) {
  HashTable ht;
  EXPECT_TRUE(ht.empty());
  ht.insert("Emma", Value(12, 34));
  EXPECT_FALSE(ht.empty());
}

TEST(HashTableTest, TestContains) {
  HashTable ht;
  srand(time(NULL));
  const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
  ht.insert("Emma", Value(9, 12));
  for (size_t i = 0; i < 2000; i++) {
    std ::string name;
    for (size_t j = 0; j < 15; j++) {
      name += alphabet[rand() % 15];
    }
    ht.insert(name, Value(i, i));
  }
  EXPECT_TRUE(ht.contains("Emma"));
  EXPECT_FALSE(ht.contains("Ann"));
  HashTable ht1;
  EXPECT_FALSE(ht1.contains("Ann"));
}

TEST(HashTableTest, TestSizeAmount) {
  HashTable ht;
  srand(time(NULL));
  const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
  EXPECT_EQ(ht.size(), 2);
  EXPECT_EQ(ht.amount(), 0);
  ht.insert("Emma", Value(9, 12));
  for (size_t i = 0; i < 2000; i++) {
    std ::string name;
    for (size_t j = 0; j < 15; j++) {
      name += alphabet[rand() % 15];
    }
    ht.insert(name, Value(i, i));
  }
  EXPECT_EQ(ht.amount(), 2001);

  EXPECT_TRUE((ht.size() > 8));
  HashTable ht1;
  EXPECT_EQ(ht1.size(), 2);
  EXPECT_EQ(ht1.amount(), 0);
}

TEST(HashTableTest, TestInsert) {
  HashTable ht;
  srand(time(NULL));
  const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
  ht.insert("Emma", Value(9, 12));
  for (size_t i = 0; i < 2000; i++) {
    std ::string name;
    for (size_t j = 0; j < 15; j++) {
      name += alphabet[rand() % 15];
    }
    ht.insert(name, Value(i, i));
  }
  EXPECT_FALSE(ht.insert("Emma", Value(26, 70)));
  EXPECT_FALSE(ht.insert("Emma", Value(9, 12)));
  EXPECT_TRUE(ht.insert("Elle", Value(56, 12)));
}

TEST(HashTableTest, TestErase) {
  HashTable ht;
  srand(time(NULL));
  const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
  ht.insert("Emma", Value(9, 12));
  for (size_t i = 0; i < 5000; i++) {
    std ::string name;
    for (size_t j = 0; j < 5; j++) {
      name += alphabet[rand() % 15];
    }
    ht.insert(name, Value(i, i));
  }
  ht.insert("Alice", Value(5, 13));
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
  EXPECT_TRUE(ht.erase("Emma"));
  EXPECT_TRUE(ht.erase("Alice"));
  EXPECT_TRUE(ht.erase("Charlie"));
  EXPECT_TRUE(ht.erase("Elle"));
  EXPECT_TRUE(ht.erase("Ann"));
  EXPECT_TRUE(ht.erase("Kate"));
  EXPECT_TRUE(ht.erase("Alex"));
  EXPECT_TRUE(ht.erase("Jenny"));
  EXPECT_TRUE(ht.erase("Chuck"));
  EXPECT_TRUE(ht.erase("Den"));
  EXPECT_TRUE(ht.erase("Nate"));
  EXPECT_TRUE(ht.erase("Blair"));
  EXPECT_FALSE(ht.erase("Emily"));
  EXPECT_TRUE(ht.amount() <= 5000);
  EXPECT_FALSE(ht.erase("Emma"));
  EXPECT_FALSE(ht.erase("Alice"));
  EXPECT_FALSE(ht.erase("Charlie"));
  EXPECT_FALSE(ht.erase("Elle"));
  EXPECT_FALSE(ht.erase("Ann"));
  EXPECT_FALSE(ht.erase("Kate"));
  EXPECT_FALSE(ht.erase("Alex"));
  EXPECT_FALSE(ht.erase("Jenny"));
  EXPECT_FALSE(ht.erase("Chuck"));
  EXPECT_FALSE(ht.erase("Den"));
  EXPECT_FALSE(ht.erase("Nate"));
  EXPECT_FALSE(ht.erase("Blair"));

  HashTable ht1;
  EXPECT_FALSE(ht1.erase("Emma"));
  EXPECT_FALSE(ht1.erase("Emmikly"));
  HashTable ht2;
  ht2.insert("Alice", Value(5, 13));
  ht2.insert("Charlie", Value(34, 130));
  ht2.insert("Elle", Value(1, 1));
  ht2.insert("Ann", Value(5, 13));
  ht2.insert("Kate", Value(7, 10));
  ht2.insert("Alex", Value(34, 130));
  ht2.insert("Jenny", Value(1, 1));
  ht2.insert("Chuck", Value(5, 13));
  ht2.insert("Den", Value(7, 10));
  ht2.insert("Nate", Value(34, 130));
  ht2.insert("Blair", Value(1, 1));
  EXPECT_TRUE(ht2.erase("Alice"));
  EXPECT_TRUE(ht2.erase("Charlie"));
  EXPECT_TRUE(ht2.erase("Elle"));
  EXPECT_TRUE(ht2.erase("Ann"));
  EXPECT_TRUE(ht2.erase("Kate"));
  EXPECT_TRUE(ht2.erase("Alex"));
  EXPECT_TRUE(ht2.erase("Jenny"));
  EXPECT_TRUE(ht2.erase("Chuck"));
  EXPECT_TRUE(ht2.erase("Den"));
  EXPECT_TRUE(ht2.erase("Nate"));
  EXPECT_TRUE(ht2.erase("Blair"));
  EXPECT_TRUE(ht2.empty());
}

TEST(HashTableTest, TestClear) {
  HashTable ht;
  srand(time(NULL));
  const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
  ht.insert("Emma", Value(9, 12));
  for (size_t i = 0; i < 2000; i++) {
    std ::string name;
    for (size_t j = 0; j < 5; j++) {
      name += alphabet[rand() % 15];
    }
    ht.insert(name, Value(i, i));
  }

  ht.clear();
  EXPECT_FALSE(ht.contains("Emma"));
  EXPECT_TRUE(ht.empty());
  EXPECT_EQ(ht.amount(), 0);
  EXPECT_EQ(ht.size(), 2);
  ht.clear();
  EXPECT_EQ(ht.amount(), 0);
  EXPECT_EQ(ht.size(), 2);
  HashTable ht1;
  ht1.clear();
  EXPECT_EQ(ht1.amount(), 0);
  EXPECT_EQ(ht1.size(), 2);
  ASSERT_TRUE(ht.insert("Emma", Value(9, 12)));
  for (size_t i = 0; i < 20; i++) {
    std::string name;
    for (size_t j = 0; j < 5; j++) {
      name += i;
    }
    EXPECT_TRUE(ht.insert(name, Value(i, i)));
  }

  for (size_t i = 0; i < 200; i++) {
    std::string name;
    for (size_t j = 0; j < 5; j++) {
      name += i;
    }
    EXPECT_TRUE(ht1.insert(name, Value(i, i)));
  }
}

TEST(HashTableTest, TestAt) {
  HashTable ht;
  srand(time(NULL));
  const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
  ht.insert("Emma", Value(9, 12));
  for (size_t i = 0; i < 2000; i++) {
    std ::string name;
    for (size_t j = 0; j < 15; j++) {
      name += alphabet[rand() % 15];
    }
    ht.insert(name, Value(i, i));
  }
  EXPECT_EQ(ht["Emma"], Value(9, 12));
  EXPECT_EQ(ht["Ann"], Value());
  EXPECT_EQ(ht.at("Emma"), Value(9, 12));
  EXPECT_THROW(ht.at("All"), std::runtime_error);
}

TEST(HashTableTest, TestEq) {
  HashTable ht;
  ht.insert("Alice", Value(5, 13));
  ht.insert("Alena", Value(7, 10));
  ht.insert("Charlie", Value(34, 130));
  ht.insert("Elle", Value(1, 1));
  ht.insert("Ann", Value(5, 13));
  ht.insert("Kate", Value(7, 10));
  ht.insert("Alex", Value(34, 130));
  ht.insert("Jenny", Value(1, 1));
  HashTable ht1;
  ht1.insert("Alice", Value(5, 13));
  ht1.insert("Alena", Value(7, 10));
  ht1.insert("Charlie", Value(34, 130));
  ht1.insert("Elle", Value(1, 1));
  ht1.insert("Ann", Value(5, 13));
  ht1.insert("Kate", Value(7, 10));
  ht1.insert("Alex", Value(34, 130));
  ht1.insert("Jenny", Value(1, 1));
  EXPECT_TRUE(ht1 == ht);
  ht.erase("Charlie");
  EXPECT_TRUE(ht1 != ht);
  HashTable ht2;
  ht2.insert("Alice", Value(5, 13));
  ht2.insert("Alena", Value(6, 10));
  ht2.insert("Charlie", Value(34, 130));
  ht2.insert("Elle", Value(1, 1));
  ht2.insert("Ann", Value(5, 13));
  ht2.insert("Kate", Value(7, 10));
  ht2.insert("Alex", Value(34, 130));
  ht2.insert("Jenny", Value(1, 1));
  EXPECT_TRUE(ht1 != ht2);
  HashTable ht5;
  ht5.insert("Alice", Value(5, 13));
  ht5.insert("Alena", Value(7, 10));
  ht5.insert("Charlie", Value(34, 130));
  ht5.insert("Elle", Value(1, 1));
  ht5.insert("Ann", Value(5, 1300));
  ht5.insert("Kate", Value(7, 10));
  ht5.insert("Alex", Value(34, 130));
  ht5.insert("Jenny", Value(1, 1));
  EXPECT_TRUE(ht1 != ht5);
  HashTable ht3;
  ht3.insert("Alice", Value(5, 13));
  ht3.insert("Elle", Value(1, 1));
  ht3.insert("Charlie", Value(34, 130));
  EXPECT_TRUE(ht1 != ht3);
  HashTable ht4;
  EXPECT_TRUE(ht4 != ht3);
  ht3.insert("Alena", Value(7, 10));
  ht3.insert("Ann", Value(5, 13));
  ht3.insert("Kate", Value(7, 10));
  ht3.insert("Alex", Value(34, 130));
  ht3.insert("Jefrey", Value(1, 1));
  EXPECT_TRUE(ht1 != ht3);
  ht3.erase("Jefrey");
  ht3.insert("Jenny", Value(1, 1));
  EXPECT_TRUE(ht1 == ht3);
}

TEST(HashTableTest, TestMoveConstructor) {
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
  HashTable ht1(std::move(ht));

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
  EXPECT_TRUE(ht.empty());

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
  EXPECT_EQ(ht1.at("Alice"), Value(5, 13));
  ht1.insert("Serena", Value(28, 75));
  EXPECT_TRUE(ht1.contains("Serena"));
  EXPECT_EQ(ht1.at("Serena"), Value(28, 75));

  HashTable ht2;
  HashTable ht3(std::move(ht2));
  EXPECT_TRUE(ht3.empty());
  ht3.insert("Name", Value(8, 9));
  EXPECT_FALSE(ht3.empty());
  EXPECT_TRUE(ht2.empty());
}

TEST(HashTableTest, TestCopyConstructor) {
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
  HashTable ht1(ht);

  EXPECT_TRUE(ht == ht1);
  ht1.insert("Name", Value(8, 9));
  EXPECT_FALSE(ht.contains("Name"));
  EXPECT_TRUE(ht1.contains("Name"));

  HashTable ht2;
  srand(time(NULL));
  const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
  for (size_t i = 0; i < 2000; i++) {
    std ::string name;
    for (size_t j = 0; j < 15; j++) {
      name += alphabet[rand() % 15];
    }
    ht2.insert(name, Value(i, i));
  }
  HashTable ht3(ht2);
  EXPECT_TRUE(ht3 == ht2);

  HashTable ht4;
  HashTable ht5(ht4);
  EXPECT_TRUE(ht4 == ht5);
  for (size_t i = 0; i < 2000; i++) {
    std ::string name;
    for (size_t j = 0; j < 15; j++) {
      name += alphabet[rand() % 15];
    }
    ht5.insert(name, Value(i, i));
  }
  EXPECT_FALSE(ht5.empty());
  EXPECT_TRUE(ht4.empty());
}

TEST(HashTableTest, TestCopyAssignment) {
  HashTable ht;
  srand(time(NULL));
  const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
  for (size_t i = 0; i < 5000; i++) {
    std ::string name;
    for (size_t j = 0; j < 15; j++) {
      name += alphabet[rand() % 15];
    }
    ht.insert(name, Value(i, i));
  }
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
  ht = ht;
  EXPECT_TRUE(ht.contains("Alice"));
  EXPECT_TRUE(ht.contains("Alena"));
  EXPECT_TRUE(ht.contains("Charlie"));
  EXPECT_TRUE(ht.contains("Elle"));
  EXPECT_TRUE(ht.contains("Ann"));
  EXPECT_TRUE(ht.contains("Kate"));
  EXPECT_TRUE(ht.contains("Alex"));
  EXPECT_TRUE(ht.contains("Jenny"));
  EXPECT_TRUE(ht.contains("Chuck"));
  EXPECT_TRUE(ht.contains("Den"));
  EXPECT_TRUE(ht.contains("Nate"));
  EXPECT_TRUE(ht.contains("Blair"));

  HashTable ht1;
  ht1 = ht;
  EXPECT_TRUE(ht == ht1);
  ht1.insert("Name", Value(8, 9));
  EXPECT_FALSE(ht.contains("Name"));
  EXPECT_TRUE(ht1.contains("Name"));

  HashTable ht2;
  for (size_t i = 0; i < 2000; i++) {
    std ::string name;
    for (size_t j = 0; j < 15; j++) {
      name += alphabet[rand() % 15];
    }
    ht2.insert(name, Value(i, i));
  }
  ht = ht2;
  EXPECT_TRUE(ht == ht2);
  EXPECT_EQ(ht.amount(), ht2.amount());

  HashTable ht4;
  ht = ht4;
  EXPECT_TRUE(ht4 == ht);
  EXPECT_TRUE(ht.empty());
  EXPECT_TRUE(ht4.empty());

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
}

TEST(HashTableTest, TestMoveAssignment) {

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
  ht1 = std::move(ht);

  EXPECT_TRUE(ht.empty());
  EXPECT_FALSE(ht1.empty());
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
  EXPECT_EQ(ht1.at("Alice"), Value(5, 13));
  ht1.insert("Serena", Value(28, 75));
  EXPECT_TRUE(ht1.contains("Serena"));
  EXPECT_EQ(ht1.at("Serena"), Value(28, 75));

  HashTable ht2;
  srand(time(NULL));
  const std ::string alphabet = "qwertyuiopasdfghjklzxcvb";
  for (size_t i = 0; i < 2000; i++) {
    std ::string name;
    for (size_t j = 0; j < 15; j++) {
      name += alphabet[rand() % 15];
    }
    ht2.insert(name, Value(i, i));
  }
  ht2 = std::move(ht1);
  EXPECT_TRUE(ht1.empty());
  EXPECT_FALSE(ht2.empty());
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
  EXPECT_EQ(ht2.at("Alice"), Value(5, 13));
  ht2.insert("Serena", Value(28, 75));
  EXPECT_TRUE(ht2.contains("Serena"));
  EXPECT_EQ(ht2.at("Serena"), Value(28, 75));

  HashTable ht3;
  ht3.insert("Allice", Value(5, 13));
  ht3.insert("Allena", Value(7, 10));
  ht3.insert("Charllie", Value(34, 130));
  ht3.insert("Ellle", Value(1, 1));
  ht3.insert("Annn", Value(5, 13));
  ht3.insert("Katte", Value(7, 10));
  ht3.insert("Allex", Value(34, 130));
  ht3.insert("Jennny", Value(1, 1));
  ht3.insert("Chuckk", Value(5, 13));
  ht3.insert("DDen", Value(7, 10));

  ht3 = std::move(ht2);
  EXPECT_TRUE(ht2.empty());
  EXPECT_FALSE(ht3.empty());
  EXPECT_TRUE(ht3.contains("Alice"));
  EXPECT_TRUE(ht3.contains("Alena"));
  EXPECT_TRUE(ht3.contains("Charlie"));
  EXPECT_TRUE(ht3.contains("Elle"));
  EXPECT_TRUE(ht3.contains("Ann"));
  EXPECT_TRUE(ht3.contains("Kate"));
  EXPECT_TRUE(ht3.contains("Alex"));
  EXPECT_TRUE(ht3.contains("Jenny"));
  EXPECT_TRUE(ht3.contains("Chuck"));
  EXPECT_TRUE(ht3.contains("Den"));
  EXPECT_TRUE(ht3.contains("Nate"));
  EXPECT_TRUE(ht3.contains("Blair"));
  EXPECT_TRUE(ht3.contains("Serena"));
  EXPECT_EQ(ht3.at("Alice"), Value(5, 13));
  ht3.insert("Lily", Value(28, 75));
  EXPECT_TRUE(ht3.contains("Lily"));
  EXPECT_EQ(ht3.at("Lily"), Value(28, 75));
  ht3 = std::move(ht3);
  EXPECT_FALSE(ht3.empty());
  EXPECT_TRUE(ht3.contains("Alice"));
  EXPECT_TRUE(ht3.contains("Alena"));
  EXPECT_TRUE(ht3.contains("Charlie"));
  EXPECT_TRUE(ht3.contains("Elle"));
  EXPECT_TRUE(ht3.contains("Ann"));
  EXPECT_TRUE(ht3.contains("Kate"));
  EXPECT_TRUE(ht3.contains("Alex"));
  EXPECT_TRUE(ht3.contains("Jenny"));
  EXPECT_TRUE(ht3.contains("Chuck"));
  EXPECT_TRUE(ht3.contains("Den"));
  EXPECT_TRUE(ht3.contains("Nate"));
  EXPECT_TRUE(ht3.contains("Blair"));
  EXPECT_TRUE(ht3.contains("Serena"));
  EXPECT_TRUE(ht3.contains("Lily"));

  HashTable ht4;
  ht3 = std::move(ht4);
  EXPECT_TRUE(ht3.empty());
}

TEST(HashTableTest, TestSwap) {

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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
