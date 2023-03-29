//learn for loop

int outer{ 1 };
while (outer <= 5)
{
	// Row elements appear in descending order, so start from 5 and loop through to 1
	int inner{ 5 };

	while (inner >= 1)
	{
		// The first number in any row is the same as the row number
		// So number should be printed only if it is <= the row number, space otherwise
		if (inner <= outer)
			std::cout << inner << ' '; // print the number and a single space
		else
			std::cout << "  "; // don't print a number, but print two spaces

		--inner;
	}

	// A row has been printed, move to the next row
	std::cout << '\n';

	++outer;
}


//Logging

#include <iostream>
#include "io.h"


int main()
{
	plog::init(plog::debug, "Logfile.log");

	PLOGD << "main() called";

	writeAnswer(readNumber() + readNumber());

}


//Gravity 

void gravityFall(double  distanceToFall)
{
	//distance fallen = gravity_constant * x_seconds² / 2;
	const double gravity{ 9.8 };
	double distanceFallen{ 0 };
	int secondsDelayed{ 0 };


	for (double currHeight{}; currHeight >= 0; secondsDelayed++)
	{
		distanceFallen = gravity * (secondsDelayed* secondsDelayed) / 2;
		currHeight = distanceToFall - distanceFallen;

		if (currHeight <= 0)
		{
			std::cout << secondsDelayed << " Sekunden vergangen. The Ball is on Earth.";
		} else
		{
			std::cout << secondsDelayed << " Sekunden vergangen. Meter gefallen: " << currHeight << "\n";
		}

	}
}


//Random

	namespace Random
{
	std::mt19937 mt{ std::random_device{}() };

	int get(int min, int max)
	{
		std::uniform_int_distribution die{ min, max }; // we can create a distribution in any function that needs it
		return die(mt); // and then generate a random number from our global generator
	}
}


//std::cin Input fix

void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
double getDouble()
{
	while (true)
	{
		std::cout << "Enter a double value: ";
		double x{};
		std::cin >> x;

		if (std::cin.fail())
		{
			std::cin.clear();
			ignoreLine();
		} else
		{
			ignoreLine();
			return x;
		}
	}
}

//isPrime

bool isPrime(int x)
{
	int temp{};

	if (x <= 1)
		return false;

	for (int i = 2; ;i++)
	{
		if ((x % i) == 0)
		{
			temp = i;
			break;
		}
	}

	if (temp == x)
		return true;
	else
		return false;
}

bool isPrime(int x)
{
	if (x <= 1)
		return false;

	for (int test{ 2 }; test <= std::sqrt(x); ++test)
	{
		if (x % test == 0)
			return false;
	}

	return true;
}

int main()
{
	assert(!isPrime(0));
	assert(!isPrime(1));
	assert(isPrime(2));
	assert(isPrime(3));
	assert(!isPrime(4));
	assert(isPrime(5));
	assert(isPrime(7));
	assert(!isPrime(9));
	assert(isPrime(11));
	assert(isPrime(13));
	assert(!isPrime(15));
	assert(!isPrime(16));
	assert(isPrime(17));
	assert(isPrime(19));
	assert(isPrime(97));
	assert(!isPrime(99));
	assert(isPrime(13417));

	std::cout << "Success!\n";

	return 0;
}

//hiLo game

#include <random>
#include <limits> // for std::numeric_limits


void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void startGame(int,int);


namespace Random
{
	std::mt19937 mt{ std::random_device{}() };

	int get(int min, int max)
	{
		std::uniform_int_distribution die{ min, max }; // we can create a distribution in any function that needs it
		return die(mt); // and then generate a random number from our global generator
	}
}

void askRestart()
{

	std::cout << "Would you like to play again (y/n)? ";

	char decide{};

	std::cin >> decide;



	switch (decide)
	{
		case 'y':
			startGame();
		case 'n':
			return;
		default:
			std::cin.clear();
			askRestart();
	}
}


void startGame(int min = 1, int max = 2)
{
	std::cout << "Let's play a game. I'm thinking of a number. You have 7 tries to guess what it is.\n";
	int numToGuess{ Random::get(min,max) };
	int numGuessed{};
	bool win{};

	if (!win)
	{
		for (int i = 1; i <= 7; i++) //7 attempts
		{
			std::cout << "Guess #" << i << ": ";
			std::cin >> numGuessed;

			if (std::cin.fail()  ) // has a previous extraction failed?
			{
				// yep, so let's handle the failure
				std::cin.clear(); // put us back in 'normal' operation mode
				ignoreLine(); // and remove the bad input
				std::cerr << "Oops, that input is invalid.  Please try again.\n";
				startGame(1,2);
			}


			if (numGuessed == 0)
			{
				std::cerr << "Oops, that input is invalid.  Please try again.\n";
				startGame();
			}

			else if (numGuessed == numToGuess)
			{
				std::cout << "Correct!You win!\n";
				win = true;
				askRestart();
				return;

			} else if (numGuessed < numToGuess)
			{
				std::cout << "Your guess is too low.\n";
			} else if (numGuessed > numToGuess)
			{
				std::cout << "Your guess is too high.\n";
			}


		}
		askRestart();
	} else
	{
		std::cout << "Sorry, you lose. The correct number was " << numToGuess << ".\n";

		askRestart();
	}
}


//hiLo offi

int getGuess(int count)
{
	while (true) // loop until user enters valid input
	{
		std::cout << "Guess #" << count << ": ";

		int guess{};
		std::cin >> guess;

		if (std::cin.fail()) // did the extraction fail?
		{
			// yep, so let's handle the failure
			std::cin.clear(); // put us back in 'normal' operation mode
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the bad input
			continue; // and try again
		}

		// We may have gotten a partial extraction (e.g. user entered '43x')
		// We'll remove any extraneous input before we proceed
		// so the next extraction doesn't fail
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return guess;
	}
}

// returns true if the user won, false if they lost
bool playGame(int guesses, int number)
{
	// Loop through all of the guesses
	for (int count{ 1 }; count <= guesses; ++count)
	{
		int guess{ getGuess(count) };

		if (guess > number)
			std::cout << "Your guess is too high.\n";
		else if (guess < number)
			std::cout << "Your guess is too low.\n";
		else // guess == number
			return true;
	}
	return false;
}

bool playAgain()
{
	// Keep asking the user if they want to play again until they pick y or n.
	while (true)
	{
		char ch{};
		std::cout << "Would you like to play again (y/n)? ";
		std::cin >> ch;

		switch (ch)
		{
			case 'y': return true;
			case 'n': return false;
		}
	}
}

int main()
{
	std::random_device rd;
	std::seed_seq seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	std::mt19937 mt{ seq }; // Create a mersenne twister, seeded using the seed sequence

	std::uniform_int_distribution die{ 1, 100 }; // generate random numbers between 1 and 100
	constexpr int guesses{ 7 }; // the user has this many guesses
	do
	{
		int number{ die(mt) }; // this is the number the user needs to guess
		std::cout << "Let's play a game. I'm thinking of a number. You have " << guesses << " tries to guess what it is.\n";
		bool won{ playGame(guesses, number) };
		if (won)
			std::cout << "Correct! You win!\n";
		else
			std::cout << "Sorry, you lose. The correct number was " << number << "\n";
	} while (playAgain());

	std::cout << "Thank you for playing.\n";
	return 0;
}

//Struct Advertising

#include <iostream>
#include <string>

struct Advertising
{
	double impressions{};
	double pressedPercentage{};
	double averagePerAdv{};
};

double earnedMoneyDay(const Advertising& adv)
{
	return adv.averagePerAdv * adv.impressions * (adv.pressedPercentage/100);
}

Advertising getEarning()
{
	Advertising temp{};

	std::cout << "Impressions: ";

	std::cin >> temp.impressions;

	std::cout << "pressedPercentage in %: ";

	std::cin >> temp.pressedPercentage;

	std::cout << "averagePerAdv: ";

	std::cin >> temp.averagePerAdv;

	return temp;


}

int main()
{


	std::cout <<"Earned: " << earnedMoneyDay(getEarning());


	return 0;
}

//Struct Fraction

struct Fraction
{
	int numerator{};
	int denominator{};
};

Fraction readFraction()
{
	Fraction frac{};

	std::cout << "Enter a value for the numerator: ";
	std::cin >> frac.numerator;

	std::cout << "Enter a value for the denominator: ";
	std::cin >> frac.denominator;

	std::cout << "\n";

	return frac;

}

constexpr Fraction operator *(const Fraction& fr1, const Fraction& fr2)
{
	return { fr1.numerator * fr2.numerator ,fr1.denominator * fr2.denominator };
}

void printFraction(Fraction fr)
{
	std::cout << "Your fractions multiplied together: "<<fr.numerator<<"/"<<fr.denominator;
}


int main()
{
	Fraction frac1{ readFraction() };
	Fraction frac2{ readFraction() };

	printFraction(frac1*frac2);

	return 0;
}


//Moster Struct Enum

#include <iostream>

enum class Monster_type
{
	ogre,
	dragon,
	orc,
	giant_spider,
	slime
};

struct Monster_info
{
	Monster_type monster{};
	std::string_view name{};
	int health{};

};

void printMonster(const Monster_info& monster)
{
	switch (monster.monster)
	{
		case Monster_type::ogre:
			{
				std::cout << "This Ogre is named " << monster.name << " and has " << monster.health << " health.\n";
				break;
			}
		case Monster_type::dragon:
			{
				std::cout << "This Dragon is named " << monster.name << " and has " << monster.health << " health.\n";
				break;
			}
		default:
			{
				std::cout << "Not existing.\n";
				break;
			}
	}
}

int main()
{
	Monster_info monster1{ {Monster_type::ogre},"Tob",100 };
	Monster_info monster2{ {Monster_type::dragon},"Drake",45 };

	printMonster(monster1);
	printMonster(monster2);

	return 0;
}


//SelectionSort

#include <iostream>
#include <iterator> // for std::size

int main()
{
	int array[]{ 20,50,10,30,40,80,60 };
	int length{ static_cast<int>(std::size(array)) - 1 };

	for (int i{ 0 }; i <= length; i++)
	{
		int minNum{ array[i] };
		int minIndex{};

		for (int j{ i }; j <= length; j++)
		{
			if (array[j] >= minNum)
			{
				minNum = array[j];
				minIndex = j;
			}
		}

		std::swap(array[i], array[minIndex]);

	}


	for (int i : array)
	{
		std::cout << i << "\n";
	}


	return 0;
}

//Bubble Sort v1

for (int iteration = 0; iteration <= length; iteration++)
	{

		for (int index{ 0 }; index < length; index++)
		{
			swapped = false;

			if (array[index] > array[index + 1])
			{
				std::swap(array[index], array[index + 1]);
				swapped = true;
			} else if (length == (index + 1)) //useless*
			{
				//std::cout << "Broke at iteration: "<<iteration;
				break;

			}

		}
		--length;
		if (!swapped )
		{
			std::cout << iteration << " iterations left\n";

		}

	}



//Bubble Sort v1.2

#include <iostream>

int main()
{
	int array[]{ 6, 14, 2, 9, 12, 1, 5, 4, 8, 11, 13, 7, 3 };
	int length{ static_cast<int>(std::size(array))  -1}; //-1

	for (int iteration = 0; iteration <= length - 1; ++iteration) //arrayLength -1 -1 wut?
	{
		bool swapped{};
		for (int index = 0; index < length; ++index)
		{
			if (array[index] > array[index + 1])
			{
				std::swap(array[index], array[index + 1]);;
				swapped = true;
			}
		}

		if (!swapped)
		{
			std::cout << "Early termination on iteration: " << iteration + 1 << "\n";
			break;
		}
	}

	for (int i : array)
	{
		std::cout << i << ' ';
	}

	return 0;
}







//Array ptr arithmetics

#include <iterator> // for std::size

bool isVowel(char ch)
{
	switch (ch)
	{
		case 'A':
		case 'a':
		case 'E':
		case 'e':
		case 'I':
		case 'i':
		case 'O':
		case 'o':
		case 'U':
		case 'u':
			return true;
		default:
			return false;
	}
}

int main()
{
	char name[]{ "Mikelangelo" };
	int arrayLength{ static_cast<int>(std::size(name) )};
	int count{};

	for (char* ptr{name}; ptr!= (arrayLength+name);++ptr )
	{
		if (isVowel(*ptr))
		{
			++count;
		}
	}
	std::cout << count;

	return 0;
}


//std::find self

int* find(int* a, int* b, int c)
{
	for (; a != b; ++a)
	{
		if (*a == c)
		{
			return a;
		} else
		{
			return b;
		}
	}
}


//std::array countItems self

enum  Item
{
	health_potions,
	torches,
	arrows
};

template <typename T, std::size_t size>
int countTotalItems(const std::array<T, size>& array)
{
	int counted{};
	for (std::size_t i{}; i < array.size();i++)
	{
		counted += array[i];
	}
	return counted;
}

int main()
{

	std::array struc{ health_potions,torches,arrows };
	struc[0] = { static_cast<Item>(2) };
	struc[1] = { static_cast<Item>(4) };
	struc[2] = { static_cast<Item>(10) };


	std::cout << countTotalItems(struc);
	std::cout << struc[torches];

	return 0;
}


//std::array countItems 

#include <array>
#include <numeric>


enum Item
{
	health_potions,
	torches,
	arrows,
	maxItems
};

using itemsArray = std::array<int, Item::maxItems>;

int countTotalItems(const itemsArray& itemsPlayer)
{
	return std::reduce(itemsPlayer.begin(), itemsPlayer.end());
}

int main()
{
	itemsArray player{ 2,4,10 };

	std::cout << countTotalItems(player);

	std::cout << player[Item::torches];
}


//std::vector Students


struct Student
{
	std::string name{};
	int grade{};
};

bool gradeCompare(Student a, Student b)
{
	return a.grade > b.grade;
}

auto getStudentsAmount()
{
	int numberOfStudents{};
	do
	{
		std::cout << "How much: ";
		std::cin >> numberOfStudents;
	} while (numberOfStudents <= 0);

	return numberOfStudents;
}

std::vector<Student> getStudents()
{
	int numberStudents{getStudentsAmount()};

	std::vector<Student> students(static_cast<std::size_t>(numberStudents));

	std::string name{};
	int grade{};

	for (int i{}; i < numberStudents; i++)
	{
		std::cout << "\nEnter name: ";
		std::getline(std::cin >> std::ws, name);

		std::cout << "Enter grade: ";
		std::cin >> grade;

		students[i] = { name,grade };
	}
	return students;
}

int main()
{
	std::vector<Student> students{ getStudents() };

	std::sort(students.begin(), students.end(), gradeCompare);

	for (int i{}; i< students.size();++i)
	{
		std::cout <<"\nName: " << students[i].name;
		std::cout <<"\nGrade: " << students[i].grade;
	}
}

//swapNum

void swapNum(int& a, int& b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

//CStyle string
void printCStyle(const char* string)
{
	while (*string != '\0')
	{
		std::cout << *string;

		++string;
	}
}


//template std::string
template <typename T, std::size_t length>
void printArray(std::array<T,length> s)
{
	for (int element : s)
	{
		std::cout << element << ' ';
	}
}

//BlackJack my //player stand fix
#include <iostream>
#include <iterator> // for std::size
#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include <numeric>
#include <cstring>
#include <random>
#include <cassert>

enum class CardSuit
{
	club,
	diamond,
	heart,
	spade,

	max_suits
};

enum class CardRank
{
	rank_2,
	rank_3,
	rank_4,
	rank_5,
	rank_6,
	rank_7,
	rank_8,
	rank_9,
	rank_10,
	rank_jack,
	rank_queen,
	rank_king,
	rank_ace,

	max_ranks
};

struct Card
{
	CardRank rank{};
	CardSuit suit{};
};

void printCard(const Card& card)
{
	switch (card.rank)
	{
		case CardRank::rank_2:      std::cout << '2';   break;
		case CardRank::rank_3:      std::cout << '3';   break;
		case CardRank::rank_4:      std::cout << '4';   break;
		case CardRank::rank_5:      std::cout << '5';   break;
		case CardRank::rank_6:      std::cout << '6';   break;
		case CardRank::rank_7:      std::cout << '7';   break;
		case CardRank::rank_8:      std::cout << '8';   break;
		case CardRank::rank_9:      std::cout << '9';   break;
		case CardRank::rank_10:     std::cout << 'T';   break;
		case CardRank::rank_jack:   std::cout << 'J';   break;
		case CardRank::rank_queen:  std::cout << 'Q';   break;
		case CardRank::rank_king:   std::cout << 'K';   break;
		case CardRank::rank_ace:    std::cout << 'A';   break;
		default:
			std::cout << '?';
			break;
	}

	switch (card.suit)
	{
		case CardSuit::club:       std::cout << 'C';   break;
		case CardSuit::diamond:    std::cout << 'D';   break;
		case CardSuit::heart:      std::cout << 'H';   break;
		case CardSuit::spade:      std::cout << 'S';   break;
		default:
			std::cout << '?';
			break;
	}
}

using deck_type = std::array<Card, 52>;
using index_type = deck_type::size_type;

deck_type createDeck()
{
	deck_type deck{};
	index_type deckCounter{};

	for (int ranks{}; ranks < static_cast<int>(CardRank::max_ranks); ++ranks)
	{
		for (int suits{}; suits < static_cast<int>(CardSuit::max_suits); ++suits)
		{
			deck[deckCounter] = { .rank{static_cast<CardRank>(ranks)}, .suit{static_cast<CardSuit>(suits)} };
			++deckCounter;
		}
	}
	return deck;
}

auto printDeck(const deck_type& deck)
{
	for (const auto& card : deck)
	{
		printCard(card);
		std::cout << ' ';
	}
	std::cout << "\n";
}

auto shuffleDeck(deck_type& deck)
{
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	//std::mt19937 g{ std::random_device{}()}; learn Random, seeding, static

	std::ranges::shuffle(deck, mt);

	return deck;
}

int getCardValue(const Card& card)
{
	switch (card.rank)
	{
		case CardRank::rank_2:        return 2;
		case CardRank::rank_3:        return 3;
		case CardRank::rank_4:        return 4;
		case CardRank::rank_5:        return 5;
		case CardRank::rank_6:        return 6;
		case CardRank::rank_7:        return 7;
		case CardRank::rank_8:        return 8;
		case CardRank::rank_9:        return 9;
		case CardRank::rank_10:
		case CardRank::rank_jack:
		case CardRank::rank_queen:
		case CardRank::rank_king:     return 10;
		case CardRank::rank_ace:      return 11;
		default:
			assert(false && "should never happen");
			return 0;
	}
}

int rIndex()   //blackjack has 312 cards in game(6 * 52). Index can be 6 times the same. (0-51)
{
	deck_type deck{ createDeck() }; // creates every time new deck
	int size{ static_cast<int>(deck.size()) - 1 };

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution die{0,size};//magical 0
	return die(mt);
}

bool playBlackjack(deck_type &deck)
{
	std::cout << "\tBlackJack\n";
	constexpr int winNum{ 21 };
	constexpr int dStand{ 17 };
	int dealerValue{ getCardValue(deck[rIndex()])};
	int playerValue{ getCardValue(deck[rIndex()]) + getCardValue(deck[rIndex()]) };

	if (getCardValue(deck[rIndex()]) == 11 && playerValue>21)
	{

	}

	for (;;)
	{
		std::cout << "=========================";
		std::cout << "\nDealer value: " << dealerValue;
		std::cout << "\nPlayer value: " << playerValue;
		std::cout << "\n=========================";

		if (playerValue == winNum || dealerValue > winNum)
		{
			return true;
		}
		else if (playerValue > winNum || dealerValue == winNum)
		{
			return false;
		}

		std::cout << "\n1# Hit or 0# Stand: ";
		bool input{};
		std::cin >> input;

		playerValue = input ? playerValue + getCardValue(deck[rIndex()]) : playerValue;

		if (dealerValue < dStand)
		{
			dealerValue += getCardValue(deck[rIndex()]);
		} else if(!input)//dealer stand
		{
			return playerValue <= dealerValue ? false : true;
		}
	}
}

int main()
{
	auto deck{ createDeck() };
	for (;;)
	{
		shuffleDeck(deck);

		//printDeck(deck);

		bool win = playBlackjack(deck);

		if (win)
		{
			std::cout << "\n~~~~~~~Player won!~~~~~~~\n\n\n";
		} else
		{
			std::cout << "\n~~~~~~Player lost!~~~~~~~\n\n\n";
		}
	}

	return 0;
}
//BlackJack official

#include <algorithm> // std::shuffle
#include <array>
#include <cassert>
#include <ctime> // std::time
#include <iostream>
#include <random> // std::mt19937

enum class CardSuit
{
	club,
	diamond,
	heart,
	spade,

	max_suits
};

enum class CardRank
{
	rank_2,
	rank_3,
	rank_4,
	rank_5,
	rank_6,
	rank_7,
	rank_8,
	rank_9,
	rank_10,
	rank_jack,
	rank_queen,
	rank_king,
	rank_ace,

	max_ranks
};

struct Card
{
	CardRank rank{};
	CardSuit suit{};
};

struct Player
{
	int score{};
};

using deck_type = std::array<Card, 52>;
using index_type = deck_type::size_type;

// Maximum score before losing.
constexpr int g_maximumScore{ 21 };

// Minimum score that the dealer has to have.
constexpr int g_minimumDealerScore{ 17 };

void printCard(const Card& card)
{
	switch (card.rank)
	{
		case CardRank::rank_2:      std::cout << '2';   break;
		case CardRank::rank_3:      std::cout << '3';   break;
		case CardRank::rank_4:      std::cout << '4';   break;
		case CardRank::rank_5:      std::cout << '5';   break;
		case CardRank::rank_6:      std::cout << '6';   break;
		case CardRank::rank_7:      std::cout << '7';   break;
		case CardRank::rank_8:      std::cout << '8';   break;
		case CardRank::rank_9:      std::cout << '9';   break;
		case CardRank::rank_10:     std::cout << 'T';   break;
		case CardRank::rank_jack:   std::cout << 'J';   break;
		case CardRank::rank_queen:  std::cout << 'Q';   break;
		case CardRank::rank_king:   std::cout << 'K';   break;
		case CardRank::rank_ace:    std::cout << 'A';   break;
		default:
			std::cout << '?';
			break;
	}

	switch (card.suit)
	{
		case CardSuit::club:       std::cout << 'C';   break;
		case CardSuit::diamond:    std::cout << 'D';   break;
		case CardSuit::heart:      std::cout << 'H';   break;
		case CardSuit::spade:      std::cout << 'S';   break;
		default:
			std::cout << '?';
			break;
	}
}

int getCardValue(const Card& card)
{
	switch (card.rank)
	{
		case CardRank::rank_2:        return 2;
		case CardRank::rank_3:        return 3;
		case CardRank::rank_4:        return 4;
		case CardRank::rank_5:        return 5;
		case CardRank::rank_6:        return 6;
		case CardRank::rank_7:        return 7;
		case CardRank::rank_8:        return 8;
		case CardRank::rank_9:        return 9;
		case CardRank::rank_10:       return 10;
		case CardRank::rank_jack:     return 10;
		case CardRank::rank_queen:    return 10;
		case CardRank::rank_king:     return 10;
		case CardRank::rank_ace:      return 11;
		default:
			assert(false && "should never happen");
			return 0;
	}
}

void printDeck(const deck_type& deck)
{
	for (const auto& card : deck)
	{
		printCard(card);
		std::cout << ' ';
	}

	std::cout << '\n';
}

deck_type createDeck()
{
	deck_type deck{};

	// We could initialize each card individually, but that would be a pain.  Let's use a loop.

	index_type index{ 0 };

	for (int suit{ 0 }; suit < static_cast<int>(CardSuit::max_suits); ++suit)
	{
		for (int rank{ 0 }; rank < static_cast<int>(CardRank::max_ranks); ++rank)
		{
			deck[index].suit = static_cast<CardSuit>(suit);
			deck[index].rank = static_cast<CardRank>(rank);
			++index;
		}
	}

	return deck;
}

void shuffleDeck(deck_type& deck)
{
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	std::shuffle(deck.begin(), deck.end(), mt);
}

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

// Returns true if the player went bust. False otherwise.
bool playerTurn(const deck_type& deck, index_type& nextCardIndex, Player& player)
{
	while (true)
	{
		if (player.score > g_maximumScore)
		{
			// This can happen even before the player had a choice if they drew 2
			// aces.
			std::cout << "You busted!\n";
			return true;
		} else
		{
			if (playerWantsHit())
			{
				int cardValue{ getCardValue(deck.at(nextCardIndex++)) };
				player.score += cardValue;
				std::cout << "You were dealt a " << cardValue << " and now have " << player.score << '\n';
			} else
			{
				// The player didn't go bust.
				return false;
			}
		}
	}
}

// Returns true if the dealer went bust. False otherwise.
bool dealerTurn(const deck_type& deck, index_type& nextCardIndex, Player& dealer)
{
	// Draw cards until we reach the minimum value.
	while (dealer.score < g_minimumDealerScore)
	{
		int cardValue{ getCardValue(deck.at(nextCardIndex++)) };
		dealer.score += cardValue;
		std::cout << "The dealer turned up a " << cardValue << " and now has " << dealer.score << '\n';

	}

	// If the dealer's score is too high, they went bust.
	if (dealer.score > g_maximumScore)
	{
		std::cout << "The dealer busted!\n";
		return true;
	}

	return false;
}

bool playBlackjack(const deck_type& deck)
{
	// Index of the card that will be drawn next. This cannot overrun
	// the array, because a player will lose before all cards are used up.
	index_type nextCardIndex{ 0 };

	// Create the dealer and give them 1 card.
	Player dealer{ getCardValue(deck.at(nextCardIndex++)) };

	// The dealer's card is face up, the player can see it.
	std::cout << "The dealer is showing: " << dealer.score << '\n';

	// Create the player and give them 2 cards.
	Player player{ getCardValue(deck.at(nextCardIndex)) + getCardValue(deck.at(nextCardIndex + 1)) };
	nextCardIndex += 2;

	std::cout << "You have: " << player.score << '\n';

	if (playerTurn(deck, nextCardIndex, player))
	{
		// The player went bust.
		return false;
	}

	if (dealerTurn(deck, nextCardIndex, dealer))
	{
		// The dealer went bust, the player wins.
		return true;
	}

	return (player.score > dealer.score);
}

int main()
{
	auto deck{ createDeck() };

	shuffleDeck(deck);

	if (playBlackjack(deck))
	{
		std::cout << "You win!\n";
	} else
	{
		std::cout << "You lose!\n";
	}

	return 0;

	//std::function Calc
#include <iostream>
#include <functional>

	int input()
	{
		std::cout << "Input: ";
		int first{ };
		std::cin >> first;

		return first;
	}

	char mathOP()
	{

		char op{};
		do
		{
			std::cout << "Operation: ";
			std::cin >> op;

		} while (op != '+' && op != '-' && op != '*' && op != '/');

		return op;
	}

	int add(int x, int y)
	{
		return x + y;
	}
	int subtract(int x, int y)
	{
		return x - y;
	}
	int multiply(int x, int y)
	{
		return x * y;
	}
	int division(int x, int y)
	{
		return x / y;
	}

	using ArithmeticFunction = std::function<int(int, int)>;

	ArithmeticFunction getArithmeticFunction(char op)
	{
		switch (op)
		{
		case '+': return &add;
		case '-': return &subtract;
		case '*': return &multiply;
		case '/': return &division;
		}
		return nullptr;
	}

	int main()
	{
		int first{ input() };
		char op{ mathOP() };
		int second{ input() };

		ArithmeticFunction fcn{ getArithmeticFunction(op) };

		std::cout << first << " " << op << " " << second << " = " << fcn(first, second);
	}

	//rek.Factorial

	int factorial(int count)
	{
		if (count <= 1)
		{
			return 1;
		} else
		{
			return factorial(count - 1) * count;
		}
	}


	int main()
	{
		for (int count{ 0 }; count < 7; ++count)
			std::cout << factorial(count) << ' ';

		return 0;
	}
	//rek.SumUp (to solve)
	//Write a recursive function that takes an integer as input and returns the sum of each individual digit in the integer (e.g. 357 = 3 + 5 + 7 = 15). Print the answer for input 93427 (which is 25). Assume the input values are positive.
	int func(int x)
	{
		if (x < 10)
		{
			return x;
		} else
		{
			return func(x / 10) + x % 10;
		}
	}

	int main()
	{
		std::cout << func(934);
		return 0;
	}


	//rek.PrintBinary (to solve)

	//3a) This one is slightly trickier. Write a program that asks the user to enter a positive integer, and then uses a recursive function to print out the binary representation for that number. Use method 1 from lesson O.4 -- Converting between binary and decimal.

	//Hint: Using method 1, we want to print the bits from the “bottom up”, which means in reverse order. This means your print statement should be after the recursive call.



	void printBinary(int x)
	{
		// Termination case
		if (x == 0)
			return;

		// Recurse to the next bit
		printBinary(x / 2);

		// Print out the remainders (in reverse order)
		std::cout << x % 2;
	}

	int main()
	{
		int x;
		std::cout << "Enter a positive integer: ";
		std::cin >> x;

		printBinary(x);
	}


	//rek.NegPrintBinary (to solve)

	//3b) Update your code from 3a to handle the case where the user may enter 0 or a negative number.

	//Here’s a sample output (assuming 32-bit integers):

	//Enter an integer: -15
	//11111111111111111111111111110001

	//Hint: You can turn a negative integer into a positive one by converting it to an unsigned integer. These have identical bit representations (the type is used to determine how to interpret the number into decimal).


	void printBinary(unsigned int n)
	{
		if (n > 1) // we only recurse if n > 1, so this is our termination case for n == 0
		{
			printBinary(n / 2);
		}

		std::cout << n % 2;
	}

	int main()
	{
		int x{};
		std::cout << "Enter an integer: ";
		std::cin >> x;

		printBinary(static_cast<unsigned int>(x));
	}

	*/

		//3 Lamdas

		double(*addNumbers1)(double, double)
	{
		[](double a, double b)
		{
			return a + b;
		}
	};
	addNumbers1(2, 3);


	std::function addNumbers2
	{
		[](double a, double b)
		{
				return a + b;
		}
	};
	addNumbers2(2, 3);


	auto addNumbers3
	{
		[](double a, double b) -> double
		{
				return a + b;
		}
	};
	addNumbers3(2, 3);


//Lambda Struct Array

#include <algorithm>
#include <array>
#include <iostream>
#include <string>


struct Student
{
	std::string name{};
	int points{};
};

int main()
{
	const std::array<Student, 8> arr{
	  { { "Albert", 3 },
		{ "Ben", 5 },
		{ "Christine", 2 },
		{ "Dan", 8 },
		{ "Enchilada", 4 },
		{ "Francis", 1 },
		{ "Greg", 3 },
		{ "Hagrid", 5 } }
	};

	const auto best{
	  std::max_element(arr.begin(), arr.end(),
	  [](Student a, Student b) -> int
{
		return (a.points > b.points);

})
	};

	std::cout << best->name << " is the best student\n";

	return 0;
}

//SquareGame
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using list_type = std::vector<int>;

namespace config
{
	constexpr int multiplierMin{ 2 };
	constexpr int multiplierMax{ 4 };
	constexpr int maximumWrongAnswer{ 4 };
}

int getRandomInt(int min, int max)
{
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	return std::uniform_int_distribution{ min, max }(mt);
}

list_type generateNumbers(int start, int count, int multiplier)
{
	list_type numbers(static_cast<list_type::size_type>(count));

	int i{ start };

	for (auto& number : numbers)
	{
		number = ((i * i) * multiplier);
		++i;
	}

	return numbers;
}

list_type generateUserNumbers(int multiplier)
{
	int start{};
	int count{};

	std::cout << "Start where? ";
	std::cin >> start;

	std::cout << "How many? ";
	std::cin >> count;

	return generateNumbers(start, count, multiplier);
}

int getUserGuess()
{
	int guess{};

	std::cout << "> ";
	std::cin >> guess;

	return guess;
}

bool findAndRemove(list_type& numbers, int guess)
{
	auto found{ std::find(numbers.begin(), numbers.end(), guess) };

	if (found == numbers.end())
	{
		return false;
	} else
	{
		numbers.erase(found);
		return true;
	}
}

int findClosestNumber(const list_type& numbers, int guess)
{
	return *std::min_element(numbers.begin(), numbers.end(), [=](int a, int b)
	{
		return (std::abs(a - guess) < std::abs(b - guess));
	});
}

void printTask(list_type::size_type count, int multiplier)
{
	std::cout << "I generated " << count
		<< " square numbers. Do you know what each number is after multiplying it by "
		<< multiplier << "?\n";
}

void printSuccess(list_type::size_type numbersLeft)
{
	std::cout << "Nice! ";

	if (numbersLeft == 0)
	{
		std::cout << "You found all numbers, good job!\n";
	} else
	{
		std::cout << numbersLeft << " number(s) left.\n";
	}
}

void printFailure(const list_type& numbers, int guess)
{
	int closest{ findClosestNumber(numbers, guess) };

	std::cout << guess << " is wrong!";

	if (std::abs(closest - guess) <= config::maximumWrongAnswer)
	{
		std::cout << " Try " << closest << " next time.\n";
	} else
	{
		std::cout << '\n';
	}
}

bool playRound(list_type& numbers)
{
	int guess{ getUserGuess() };

	if (findAndRemove(numbers, guess))
	{
		printSuccess(numbers.size());

		return !numbers.empty();
	} else
	{
		printFailure(numbers, guess);
		return false;
	}
}

int main()
{
	int multiplier{ getRandomInt(config::multiplierMin, config::multiplierMax) };
	list_type numbers{ generateUserNumbers(multiplier) };

	printTask(numbers.size(), multiplier);

	while (playRound(numbers))
		;

	return 0;
}

//BinarySearch array
#include <iostream>
#include <iterator>
#include <cmath>
#include <numeric>

int binarySearch(const int* array, int target, int min, int max, int FIRST_ATTEMPT)
{
	int mid{ max / 2 };
	for (;; )
	{
		if (target == array[mid])
		{
			return mid;
		}
		if (target < array[mid])
		{
			max = mid - 1;
			mid = max / 2;
		}
		if (target > array[mid])
		{
			min = mid + 1;
			mid = min + ((max - min) / 2);
		}
		if (max < 0 || min > 14 || min > max)
		{
			return -1;
		}
	}
}

int binarySearch(const int* array, int target, int min, int max, bool ITERATIVE)
{
	for (;min<=max;)
	{
		int mid{ std::midpoint(min,max) };

		if (target < array[mid])
		{
			max = mid - 1;
		}
		else if (target > array[mid])
		{
			min = mid + 1;
		} else
		{
			return mid;
		}
	}
	return -1;
}

int binarySearch(const int* array, int target, int min, int max)
{
	for (;min <= max;)
	{
		int mid{ std::midpoint(min,max) };

		if (target < array[mid])
		{
			binarySearch(array, target, min,max = mid - 1);
		} else if (target > array[mid])
		{
			binarySearch(array, target, min = mid + 1, max);;
		} else
		{
			return mid;
		}
	}
	return -1;
}

int main()
{
	constexpr int array[]{ 3, 6, 8, 12, 14, 17, 20, 21, 26, 32, 36, 37, 42, 44, 48 };

	constexpr int numTestValues{ 9 };
	constexpr int testValues[numTestValues]{ 0, 3, 12, 13, 22, 26, 43, 44, 49 };
	int expectedValues[numTestValues]{ -1, 0, 3, -1, -1, 8, -1, 13, -1 };


	for (int count{ 0 }; count < numTestValues; ++count)
	{

		int index{ binarySearch(array, testValues[count], 0, static_cast<int>(std::size(array)) - 1) };

		if (index == expectedValues[count])
			std::cout << "test value " << testValues[count] << " passed!\n";
		else
			std::cout << "test value " << testValues[count] << " failed.  There's something wrong with your code!\n";
	}

	return 0;
}

//Stack Class
class Stack
{
private:
	const static int length{10};
	int array[length];
	//const int size_arr{static_cast<int>(std::size(array))-1};
	int stack{};

public:
	auto reset()
	{
		for (int i{}; i < length; i++)
			array[i] = 0;
	}
	auto push(int a)
	{
		if (stack != length)
		{
			array[stack] = a;
			++stack;
			return true;
		}
		return false;
	}
	auto pop()
	{
		assert(stack != 0 && "Can not pop empty stack");
		--stack;
		array[stack] = 0;

	}
	auto print()
	{
		std::cout << "(";
		for (auto& s : array)
		{
			if (s != 0) std::cout << s << " ";
		}
		std::cout <<  ")\n";
	}
};


//Member List Initialization
class RGBA
{
	using type = std::uint8_t;
private:
	type m_red{}, m_green{}, m_blue{}, m_alpha{255};

public:
	RGBA(type red, type green, type blue, type alpha = 255) :
		m_red{ red }, m_green{ green }, m_blue{ blue }, m_alpha{ alpha }{}

	void print() {std::cout << (int)m_red << "\n" << (int)m_green << "\n" << (int)m_blue << "\n" << (int)m_alpha << "\n";}
};

//Calc Class
class Calc
{
private:
	int m_value{};
public:
	Calc& add(int value) { m_value += value; return *this; }
	Calc& subs(int value) { m_value -= value; return *this; }
	Calc& mult(int value) { m_value *= value; return *this; }
	//Calc calc{};
	//calc.add(2).mult(2).subs(2);
};


//Timing code
#include <chrono> // for std::chrono functions
#include <cstddef> // for std::size_t
#include <iostream>
#include <numeric> // for std::iota

class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using clock_type = std::chrono::steady_clock;
	using second_type = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_type> m_beg{ clock_type::now() };

public:

	void reset()
	{
		m_beg = clock_type::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
	}
};

int main()
{
	Timer t;
	std::cout << t.elapsed();
	return 0;
}


//random monster generator 
#include <iostream>
#include <array>

class Monster
{
public:
	enum Type
	{
		dragon,
		goblin,
		ogre,
		orc,
		skeleton,
		troll,
		vampire,
		zombie,

		max_monster_types
	};

private:
	Type m_type{};
	std::string m_name{};
	std::string m_roar{};
	int m_points{};

public:
	Monster(Type type, const std::string& name, const std::string& roar, int points) :
		m_type{ type },
		m_name{ name },
		m_roar{ roar },
		m_points{ points }
	{}

	std::string getTypeString() const
	{
		switch(m_type)
		{
			case Type::dragon: return "dragon";
			case Type::goblin: return "goblin";
			case Type::ogre: return "ogre";
			case Type::orc: return "orc";
			case Type::skeleton: return "skeleton";
			case Type::troll: return "troll";
			case Type::vampire: return "vampire";
			case Type::zombie: return "zombie";
			default: return "???";
		}
	}

	void print()
	{
		std::cout << m_name<<" the "<< getTypeString() << " has "<<m_points <<" hit points and says "<<m_roar;
	}
};

class MonsterGenerator
{
public:
	static Monster generateMonster()
	{
		Monster::Type monster{ static_cast<Monster::Type>(getRandomNumber(0,static_cast<int>(Monster::Type::max_monster_types)-1)) };
		int points{ getRandomNumber(1,100) };

		static std::array<std::string, 6> s_names = { "M1", "M2","M3","M4","M5","M6" };
		static std::array<std::string, 6> s_roars = { "R1", "R2","R3","R4","R5","R6" };

		std::string name{ s_names[getRandomNumber(0,static_cast<int>(s_names.size() - 1))] };
		std::string roar{ s_roars[getRandomNumber(0,static_cast<int>(s_roars.size() - 1))] };

		return Monster(monster, name, roar, points);
	}

	static int getRandomNumber(int min, int max)
	{
		static constexpr double fraction{ 1.0 / (static_cast<double>(RAND_MAX) + 1.0) };
		return static_cast<int>(std::rand() * fraction * (max - min + 1) + min);
	}
};

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
	std::rand(); // If using Visual Studio, discard first random value

	Monster m{ MonsterGenerator::generateMonster() };
	m.print();

	return 0;
}

//MOD ASCII
/*
 
    ::std::wcout <<
        L"  ███▄ ▄███▓ ▒█████   ▓█████▄       ███▄ ▄███▓▓█████ ███▄    █  █    ██\n"
        L" ▓██▒▀█▀ ██▒▒██▒  ██▒ ▒██▀ ██▌     ▓██▒▀█▀ ██▒▓█   ▀ ██ ▀█   █  ██  ▓██▒\n"
        L" ▓██    ▓██░▒██░  ██▒ ░██   █▌     ▓██    ▓██░▒███  ▓██  ▀█ ██▒▓██  ▒██░\n"
        L" ▒██    ▒██ ▒██   ██░▒░▓█▄   ▌     ▒██    ▒██ ▒▓█  ▄▓██▒  ▐▌██▒▓▓█  ░██░\n"
        L"▒▒██▒   ░██▒░ ████▓▒░░░▒████▓     ▒▒██▒   ░██▒░▒████▒██░   ▓██░▒▒█████▓\n"
        L"░░ ▒░   ░  ░░ ▒░▒░▒░ ░ ▒▒▓  ▒     ░░ ▒░   ░  ░░░ ▒░ ░ ▒░   ▒ ▒  ▒▓▒ ▒ ▒\n"
        L"░░  ░      ░  ░ ▒ ▒░   ░ ▒  ▒     ░░  ░      ░ ░ ░  ░ ░░   ░ ▒░ ░▒░ ░ ░\n"
        L" ░      ░   ░ ░ ░ ▒    ░ ░  ░      ░      ░      ░     ░   ░ ░   ░░ ░ ░\n"
        L"░       ░       ░ ░      ░        ░       ░      ░           ░    ░\n";

 



    ::std::wcout <<
        L"███╗   ███╗ ██████╗ ██████╗     ███╗   ███╗███████╗███╗   ██╗██╗   ██╗\n"
        L"████╗ ████║██╔═══██╗██╔══██╗    ████╗ ████║██╔════╝████╗  ██║██║   ██║\n"
        L"██╔████╔██║██║   ██║██║  ██║    ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║\n"
        L"██║╚██╔╝██║██║   ██║██║  ██║    ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║\n"
        L"██║ ╚═╝ ██║╚██████╔╝██████╔╝    ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝\n"
        L"╚═╝     ╚═╝ ╚═════╝ ╚═════╝     ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝\n";
  
    ::std::wcout <<
        L" __       __  ______  _______       __       __ ________ __    __ __    __\n"
        L"|  \\     /  \\/      \\|       \\     |  \\     /  \\        \\  \\  |  \\  \\  |  \\\n"
        L"| ▓▓\\   /  ▓▓  ▓▓▓▓▓▓\\ ▓▓▓▓▓▓▓\\    | ▓▓\\   /  ▓▓ ▓▓▓▓▓▓▓▓ ▓▓\\ | ▓▓ ▓▓  | ▓▓\n"
        L"| ▓▓▓\\ /  ▓▓▓ ▓▓  | ▓▓ ▓▓  | ▓▓    | ▓▓▓\\ /  ▓▓▓ ▓▓__   | ▓▓▓\\| ▓▓ ▓▓  | ▓▓\n"
        L"| ▓▓▓▓\\  ▓▓▓▓ ▓▓  | ▓▓ ▓▓  | ▓▓    | ▓▓▓▓\\  ▓▓▓▓ ▓▓  \\  | ▓▓▓▓\\ ▓▓ ▓▓  | ▓▓\n"
        L"| ▓▓\\▓▓ ▓▓ ▓▓ ▓▓  | ▓▓ ▓▓  | ▓▓    | ▓▓\\▓▓ ▓▓ ▓▓ ▓▓▓▓▓  | ▓▓\\▓▓ ▓▓ ▓▓  | ▓▓\n"
        L"| ▓▓ \\▓▓▓| ▓▓ ▓▓__/ ▓▓ ▓▓__/ ▓▓    | ▓▓ \\▓▓▓| ▓▓ ▓▓_____| ▓▓ \\▓▓▓▓ ▓▓__/ ▓▓\n"
        L"| ▓▓  \\▓ | ▓▓\\▓▓    ▓▓ ▓▓    ▓▓    | ▓▓  \\▓ | ▓▓ ▓▓     \\ ▓▓  \\▓▓▓\\▓▓    ▓▓\n"
        L" \\▓▓      \\▓▓ \\▓▓▓▓▓▓ \\▓▓▓▓▓▓▓      \\▓▓      \\▓▓\\▓▓▓▓▓▓▓▓\\▓▓   \\▓▓ \\▓▓▓▓▓▓\n";

*/
