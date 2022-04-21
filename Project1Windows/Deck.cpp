#include "Deck.h"
#include <random> // std::mt19937
#include <algorithm> // std::shuffle
#include <iostream>
#include <cassert>

Deck::Deck()
{
    std::size_t index{ 0 };

    for (int suit{ 0 }; suit < static_cast<int>(Card::max_suits); ++suit)
    {
        for (int rank{ 0 }; rank < static_cast<int>(Card::max_ranks); ++rank)
        {
            m_deck[index] = { static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit) };
            ++index;
        }
    }
}

void Deck::shuffle()
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

    std::shuffle(m_deck.begin(), m_deck.end(), mt);

    m_cardIndex = 0;
}

void Deck::print()
{
    for (const auto& card : m_deck)
    {
        card.print();
        std::cout << ' ';
    }

    std::cout << '\n';
}