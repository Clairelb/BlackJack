#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include "blackjack.h"

using namespace std;

//Card constructor
Card::Card(Card::Rank rank, Card::Type type) {
	this->rank = rank;
	this->type = type;
}

int Card::getValue() {
	Rank rank = this->rank;
	switch (rank) {
	case Card::Rank::ACE: return 1;
	case Card::Rank::TWO: return 2;
	case Card::Rank::THREE: return 3;
	case Card::Rank::FOUR: return 4;
	case Card::Rank::FIVE: return 5;
	case Card::Rank::SIX: return 6;
	case Card::Rank::SEVEN: return 7;
	case Card::Rank::EIGHT: return 8;
	case Card::Rank::NINE: return 9;
	case Card::Rank::TEN: return 10;
	case Card::Rank::JACK: return 10;
	case Card::Rank::QUEEN: return 10;
	case Card::Rank::KING: return 10;
	}
}

void Card::displayCard() {
	Rank rank = this->rank;
	Type type = this->type;

	switch (rank) {
	case Card::Rank::ACE: cout << '1'; break;
	case Card::Rank::TWO: cout << '2'; break;
	case Card::Rank::THREE: cout << '3'; break;
	case Card::Rank::FOUR: cout << '4'; break;
	case Card::Rank::FIVE: cout << '5'; break;
	case Card::Rank::SIX: cout << '6'; break;
	case Card::Rank::SEVEN: cout << '7'; break;
	case Card::Rank::EIGHT: cout << '8'; break;
	case Card::Rank::NINE: cout << '9'; break;
	case Card::Rank::TEN: cout << "10"; break;
	case Card::Rank::JACK: cout << 'J'; break;
	case Card::Rank::QUEEN: cout << 'Q'; break;
	case Card::Rank::KING: cout << 'K'; break;
	}

	switch (type) {
	case Card::Type::CLUBS: cout << 'C'; break;
	case Card::Type::DIAMONDS: cout << 'D'; break;
	case Card::Type::HEARTS: cout << 'H'; break;
	case Card::Type::SPADES: cout << 'S'; break;
	}
}

//hand constructor
Hand::Hand() { }

//adding card c to the end of the hand
void Hand::add(Card c) {
	(this->hand).push_back(c);
}

//removing all the cards from a hand
void Hand::clear() {
	(this->hand).clear();
}

//adding all the card's values to determine the total of a hand
int Hand::getTotal() {
	vector<Card> hand = this->hand;
	int size = hand.size();
	int i = 0;
	int value = 0;
	for (i; i < size; i++) {
		Card card = hand.at(i);
		value += card.getValue();
	}
	return value;
}

//deck constructor
Deck::Deck() { }

//creating 52 cards to populate the deck
void Deck::populate() {
	vector<Card::Rank> ranks{ Card::Rank::ACE, Card::Rank::TWO, Card::Rank::THREE, Card::Rank::FOUR, Card::Rank::FIVE, Card::Rank::SIX,
		Card::Rank::SEVEN, Card::Rank::EIGHT, Card::Rank::NINE, Card::Rank::TEN, Card::Rank::JACK, Card::Rank::QUEEN, Card::Rank::KING };

	vector<Card::Type> types{ Card::Type::CLUBS, Card::Type::DIAMONDS, Card::Type::HEARTS, Card::Type::SPADES };

	for (int i = 0; i < types.size(); i++) {
		for (int x = 0; x < ranks.size(); x++) {
			Card c(ranks[x], types[i]);
			(this->deck).push_back(c);
		}
	}
}

//swapping all the cards in the deck around to shuffle it
void Deck::shuffle() {
	srand((unsigned)time(0));
	for (int i = 0; i < 52; i++) {
		swap(deck[i], deck[rand() % 52]);
	}
}

//dealing a card to the specified hand and removing that card from the deck
void Deck::deal(Hand &h) {
	Card c = (this->deck).front();
	h.add(c);
	deck.erase(deck.begin());
}

//if the hand's total > 21 the player busted
bool AbstractPlayer::isBusted(Hand h) {
	int total = h.getTotal();
	if (total > 21) return true;
	else return false;
}

//asking the user if they wish to draw another card
bool HumanPlayer::isDrawing() const {
	char answer;
	cout << "Do you want to draw another card? [y/n]: ";
	cin >> answer;
	if (answer == 'y') return true;
	else return false;
}

//the function prints who won the round depending on the char winner passed to it
//'c' - casino wins, 'p' - player wins, 't' - it's a tie
void HumanPlayer::announce(char winner) {
	switch (winner) {
	case 'c':
		cout << "Casino wins. Better luck next time" << endl;
		break;
	case 'p':
		cout << "Player wins ! Congratulations" << endl;
		break;
	case 't':
		cout << "Push. No one wins" << endl;
		break;
	default:
		break;
	}
}

void ComputerPlayer::setHand(Hand h) {
	this->hand = h;
}

//if the casino's hands is <= 16 it keeps drawing cards
bool ComputerPlayer::isDrawing() const {
	Hand h = this->hand;
	int total = h.getTotal();
	if (total <= 16) return true;
	else return false;
}

void BlackJackGame::play() {
	//creating and shuffling the deck
	m_deck.populate();
	m_deck.shuffle();

	//dealing the casino's first card
	Hand hComp = m_casino.hand;
	m_deck.deal(hComp);
	m_casino.setHand(hComp);

	//displaying the computer's hand and total
	cout << "Casino: ";
	int sizeC = hComp.hand.size();
	for (int i = 0; i < sizeC; i++) {
		Card c = hComp.hand.at(i);
		c.displayCard();
		cout << " ";
	}
	cout << "[" << to_string(hComp.getTotal()) << "]" << endl;

	//dealing the player's first 2 cards
	HumanPlayer player;
	Hand hPlayer = player.hand;
	m_deck.deal(hPlayer);
	m_deck.deal(hPlayer);

	//displaying the player's hand and total
	cout << "Player: ";
	int sizeP = hPlayer.hand.size();
	for (int i = 0; i < sizeP; i++) {
		Card c = hPlayer.hand.at(i);
		c.displayCard();
		cout << " ";
	}
	cout << "[" << to_string(hPlayer.getTotal()) << "]" << endl;

	//player's turn to play
	bool isDrawingP = player.isDrawing();
	while (isDrawingP) {
		m_deck.deal(hPlayer);

		//displaying the player's hand and total
		cout << "Player: ";
		int sizeP = hPlayer.hand.size();
		for (int i = 0; i < sizeP; i++) {
			Card c = hPlayer.hand.at(i);
			c.displayCard();
			cout << " ";
		}
		cout << "[" << to_string(hPlayer.getTotal()) << "]" << endl;

		//checking if the player busted
		//if yes, the casino wins and the round ends
		bool isBusted = player.isBusted(hPlayer);
		if (isBusted == true) {
			cout << "Player busts." << endl;
			player.announce('c');
			hComp.clear();
			m_casino.setHand(hComp);
			hPlayer.clear();
			return;
		}

		//checking if the player wants to draw once more
		isDrawingP = player.isDrawing();
	}

	//computer's turn to play
	bool isDrawingC = m_casino.isDrawing();
	while (isDrawingC) {
		m_deck.deal(hComp);
		m_casino.setHand(hComp);

		//displaying the computer's hand and total
		cout << "Casino: ";
		int sizeC = hComp.hand.size();
		for (int i = 0; i < sizeC; i++) {
			Card c = hComp.hand.at(i);
			c.displayCard();
			cout << " ";
		}
		cout << "[" << to_string(hComp.getTotal()) << "]" << endl;

		//checking if the casino busted
		//if yes, player wins and the round ends
		bool isBusted = player.isBusted(hComp);
		if (isBusted == true) {
			cout << "Casino busts." << endl;
			player.announce('p');
			hComp.clear();
			m_casino.setHand(hComp);
			hPlayer.clear();
			return;
		}

		//checking if the casino will draw once more
		isDrawingC = m_casino.isDrawing();
	}

	//checking for the winner
	int totalC = hComp.getTotal();
	int totalP = hPlayer.getTotal();

	//checking for a tie
	if (totalC == totalP) {
		player.announce('t');
		hComp.clear();
		m_casino.setHand(hComp);
		hPlayer.clear();
		return;
	}

	//announcing the winner of the game: 'p' - player wins, 'c' - casino wins
	char winner = (totalC < totalP ? 'p' : 'c');
	player.announce(winner);

	//clearing the hands for the next round
	hComp.clear();
	m_casino.setHand(hComp);
	hPlayer.clear();
}