#include "blackjack.h"

int main() {
	cout << "\tWelcome to the Comp322 BlackJack game!" << endl << endl;

	BlackJackGame game;

	//Main loop of the game
	bool playAgain = true;
	char answer = 'y';
	while (playAgain) {
		game.play();

		//Check whether the player would like to play another round
		cout << "Would you like another round? [y/n]: ";
		cin >> answer;
		cout << endl << endl;
		playAgain = (answer == 'y' ? true : false);
	}

	cout << "Game Over !";
	return 0;
}