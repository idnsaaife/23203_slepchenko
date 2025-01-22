#pragma once
#include <iostream>
#include <string>

enum class Suit
{
    Hearts,
    Diamonds,
    Clubs,
    Spades,
    NoSuit,
};

enum class Rank
{
    One = 1,
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack = 10,
    Queen = 10,
    King = 10,
    Ace = 11
};

class Card
{
private:
    Suit suit = Suit::NoSuit;
    Rank rank;

public:
    Card() = delete;
    Card(Card &&other) noexcept = default;
    Card(const Card &other) = default;
    Card &operator=(Card &&other) noexcept = default;
    Card &operator=(const Card &other) noexcept = default;
    Rank getRank() const { return rank; }
    Card(Rank r, Suit s = Suit::NoSuit) : suit(s), rank(r) {};

    void showCard() const;
};
