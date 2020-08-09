#include <vector>
#include <iostream>

using namespace std;

class Card {

public:
	enum class Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
	enum class Type { CLUBS, DIAMONDS, HEARTS, SPADES };

	Card(Rank rank, Type type);

	int getValue();
	void displayCard();

private:
	Rank rank;
	Type type;
};


class Hand {

public:
	vector<Card> hand;
	Hand();
	void add(Card c);
	void clear();
	int getTotal();
};


class Deck {

private:
	vector<Card> deck;

public:
	Deck();
	void populate();
	void shuffle();
	void deal(Hand &h);
};


class AbstractPlayer {

public:
	virtual bool isDrawing() const = 0;
	bool isBusted(Hand h);
};


class HumanPlayer : public AbstractPlayer {

public:
	Hand hand;
	bool isDrawing() const;
	void announce(char status);
};


class ComputerPlayer : public AbstractPlayer {

public:
	Hand hand;
	bool isDrawing() const;
	void setHand(Hand h);
};


class BlackJackGame {

private:
	Deck m_deck;
	ComputerPlayer m_casino;

public:
	void play();
};
