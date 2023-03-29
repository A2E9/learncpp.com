#pragma once
#include "Deck.h"

class Player
{
private:
	int m_score{};

public:
	Player() = default;

	auto drawCard(Deck& deck)
	{	
		int value = deck.dealCard().value();
        m_score += value;
        return value;
		
	}

	int score() const { return m_score; }

	bool isBust() const { return (m_score > 21); }



};