#include "headers/deck.h"

Deck::Deck(const std::string &type)
{
    if (type == "rand")
    {
        for (unsigned int rank = 1; rank <= 10; rank++)
        {
            cards.push_back(Card(static_cast<Rank>(rank)));
        }
    }

    else if (type == "simple")
    {
        for (unsigned int suit = 0; suit < 4; ++suit)
        {
            for (unsigned int rank = 2; rank <= 9; ++rank)
            {
                cards.push_back(Card(static_cast<Rank>(rank), static_cast<Suit>(suit)));
            }
            cards.push_back(Card(Rank::Ten, static_cast<Suit>(suit)));
            cards.push_back(Card(Rank::Jack, static_cast<Suit>(suit)));
            cards.push_back(Card(Rank::Queen, static_cast<Suit>(suit)));
            cards.push_back(Card(Rank::King, static_cast<Suit>(suit)));
            cards.push_back(Card(Rank::Ace, static_cast<Suit>(suit)));
        }
    }

    else
    {
        size_t N = std::stoi(type);
        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int suit = 0; suit < 4; ++suit)
            {
                for (unsigned int rank = 2; rank <= 9; ++rank)
                {
                    cards.push_back(Card(static_cast<Rank>(rank), static_cast<Suit>(suit)));
                }
                cards.push_back(Card(Rank::Ten, static_cast<Suit>(suit)));
                cards.push_back(Card(Rank::Jack, static_cast<Suit>(suit)));
                cards.push_back(Card(Rank::Queen, static_cast<Suit>(suit)));
                cards.push_back(Card(Rank::King, static_cast<Suit>(suit)));
                cards.push_back(Card(Rank::Ace, static_cast<Suit>(suit)));
            }
        }
    }
    shuffleDeck();
}

void Deck::shuffleDeck()
{
    std::shuffle(cards.begin(), cards.end(), rng);
}

const Card &Deck::giveCard()
{
    if (cards.empty())
    {
        throw std::runtime_error("Deck is empty. Cannot give a card.");
    }
    const Card &current = cards.back();
    cards.pop_back();
    return current;
}

size_t Deck::size() const
{
    return cards.size();
}