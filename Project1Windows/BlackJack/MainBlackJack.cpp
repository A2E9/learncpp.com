#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Player.h"


bool playerWantsHit()
{
    while (true)
    {
        std::cout << "(h) to hit, or (s) to stand: ";

        char ch{};
        std::cin >> ch;

        switch (ch)
        {
            case 'h':
                return true;
            case 's':
                return false;
        }
    }
}

bool playerTurn(Deck& deck, Player& player)
{
    while (true)
    {
        if (player.isBust())
        {
            std::cout << "You busted!\n";
            return true;
        } else
        {
            if (playerWantsHit())
            {
                int playerCard{ player.drawCard(deck) };
                std::cout << "You were dealt a " << playerCard << " and now have " << player.score() << '\n';
            } else
            {
                return false;
            }
        }
    }
}

bool dealerTurn(Deck& deck, Player& dealer)
{
    while (dealer.score() < 17)
    {
        int dealerCard{ dealer.drawCard(deck) };
        std::cout << "The dealer turned up a " << dealerCard << " and now has " << dealer.score() << '\n';
    }

    if (dealer.isBust())
    {
        std::cout << "The dealer busted!\n";
        return true;
    }
    return false;
}

bool playBlackjack(Deck& deck)
{
    Player dealer{};
    dealer.drawCard(deck);

    std::cout << "The dealer is showing: " << dealer.score() << '\n';

    Player player{};
    player.drawCard(deck);
    player.drawCard(deck);

    std::cout << "You have: " << player.score() << '\n';

    if (playerTurn(deck, player))
    {
        return false;
    }

    if (dealerTurn(deck, dealer))
    {
        return true;
    }

    return (player.score() > dealer.score());
}
int mainBlackJack()
{
    Deck deck{};

    deck.shuffle();

    if (playBlackjack(deck))
    {
        std::cout << "You win!\n";
    } else
    {
        std::cout << "You lose!\n";
    }
    return 0;
}





