#include "headers/card.h"

void Card::showCard() const
{
    std::string rank_str;
    if (rank == Rank::One)
        rank_str = "One";
    if (rank == Rank::Two)
        rank_str = "Two";
    else if (rank == Rank::Three)
        rank_str = "Three";
    else if (rank == Rank::Four)
        rank_str = "Four";
    else if (rank == Rank::Five)
        rank_str = "Five";
    else if (rank == Rank::Six)
        rank_str = "Six";
    else if (rank == Rank::Seven)
        rank_str = "Seven";
    else if (rank == Rank::Eight)
        rank_str = "Eight";
    else if (rank == Rank::Nine)
        rank_str = "Nine";
    else if (rank == Rank::Ten)
        rank_str = "Ten";
    else if (rank == Rank::Jack)
        rank_str = "Jack";
    else if (rank == Rank::Queen)
        rank_str = "Queen";
    else if (rank == Rank::King)
        rank_str = "King";
    else if (rank == Rank::Ace)
        rank_str = "Ace";

    std::string suit_str;
    if (suit == Suit::Hearts)
        suit_str = " of Hearts";
    else if (suit == Suit::Diamonds)
        suit_str = " of Diamonds";
    else if (suit == Suit::Clubs)
        suit_str = " of Clubs";
    else if (suit == Suit::Spades)
        suit_str = " of Spades";
    else if (suit == Suit::NoSuit)
        suit_str = "";

    std::cout << rank_str + suit_str << std::endl;
}