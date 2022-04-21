#pragma once
#include <array>
#include <cassert>
#include "Card.h"

class Deck
{
private:
	std::array<Card, 52> m_deck{};
    int m_cardIndex{0};

public:
    Deck();

    void shuffle();
    void print();

    const Card& dealCard()
    {
        assert(m_cardIndex < m_deck.size());
        //return m_deck.at(m_cardIndex++);
        return m_deck[m_cardIndex++];
    }


};

