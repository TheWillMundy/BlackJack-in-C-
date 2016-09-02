// BlackJack Project.cpp : Defines the entry point for the console application.
//

//C++ Fairy - my program is *probably* all ok (after hours of testing i think its completely ok) 
//Please advise me - is there anything else I should/can add to my game in the next few hours?
//Or, can you give a rough outline on how I could make a hangman game?
#include "stdafx.h"
#include <iostream>
#include "card.h"
#include <time.h>

//methods
void createDeck();
void randomize();
void deal();
void reset();
int blackJackValue(int value, int totalCardValue);
void player1Turn();
void player1CardValue();
void specialCaseAce();
//void normAITurn();
//void hardAITurn();
void aiTurn();
void aiCV();
void displayAllCards();


//global variables
int topCard = 0;
card deck[52];

//player 1 variables
int p1Size = 0;
int p1Cash = 100;
int p1Bet = 0;
int p1CardValue = 0;
bool p1HasAce = false;
bool busted = false;
bool won = false;

//ai variables
int aiSize = 0;
int aiCardValue = 0;
bool aiHasAce = false;

//player card arrays
card player1[12];
card ai[12];

//keep playing variable
bool saidYes = true;
bool roundEnded = false;

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	cout << "Welcome to BlackJack! You're playing against the dealer, good luck!" << endl;
	string answer;
	cout << "***********************************************************" << endl;
	while (saidYes == true && p1Cash != 0) {
		roundEnded = false;
		createDeck();
		randomize();
		deal();
		bool error = true;
		while (error = true) {
			cout << "You have $" << p1Cash << " in cash. What would you like to bet on this match?" << endl;
			cout << "Your bet: ";
			cin >> p1Bet;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> p1Bet;
			}
			if (p1Bet > p1Cash || p1Bet < 0) {
				cout << "Unfortunately, you cannot bet that value. Please try again." << endl;
				p1Bet = 0;
			}
			else {
				cout << "That is a valid bet. Enjoy the game!" << endl;
				error = false;
				break;
			}
		}
		player1CardValue();
		player1Turn();
		aiCV();
		if (busted == false) {
			aiTurn();
		}
		else {
			won = false;
		}
		displayAllCards();
		cout << "*********************************" << endl;
		if (won == true) {
			p1Cash += p1Bet;
			cout << "Congratulations, you won your bet of " << p1Bet << "! You now have: " << p1Cash << "." << endl;
		}
		else {
			p1Cash -= (p1Bet);
			cout << "Aw, you lost - that's too bad. Unfortunately, you lost your bet of " << p1Bet << ", so you now have: " << p1Cash << "." << endl;
		}
		if (p1Cash == 0) {
			cout << "You do not have any more money to play. Well, looks like it is time to bid farewell. We hope to see you back here at the Princeton Bay Sands!" << endl;
			break;
		}
		cout << "Would you like to play again?" << endl;
		cin >> answer;
		if (answer == "no" || answer == "No") {
			saidYes = false;
		}
		reset();
	}


}

void createDeck() {
	for (int i = 1; i < 14; i++) {
		deck[i - 1] = card(i, "Spades");
	}
	for (int i = 1; i < 14; i++) {
		deck[i + 12] = card(i, "Diamonds");
	}
	for (int i = 1; i < 14; i++) {
		deck[i + 25] = card(i, "Hearts");
	}
	for (int i = 1; i < 14; i++) {
		deck[i + 38] = card(i, "Clubs");
	}
}

void randomize() {
	for (int i = 0; i < 52; i++) {
		card tempCard = deck[i];
		int randCard = rand() % 51 + 1;
		deck[i] = deck[randCard];
		deck[randCard] = tempCard;
	}
}

void deal()
{
	for (int i = 0; i < 2; i++) {
		player1[i] = deck[topCard];
		if (player1[i].getValue() == 1) {
			p1HasAce = true;
		}
		topCard++;
		p1Size++;

		ai[i] = deck[topCard];
		if (player1[i].getValue() == 1) {
			aiHasAce = true;
		}
		topCard++;
		aiSize++;
	}
}

void reset()
{
	for (int i = 0; i < 2; i++)
	{
		player1[i] = card();
		ai[i] = card();
	}
	topCard = 0;
	p1Size = 0;
	aiSize = 0;
	createDeck();
	aiCardValue = 0;
	p1CardValue = 0;
	busted = false;
	p1HasAce = false;
	aiHasAce = false;
	won = false;
	p1Bet = 0;
}


int blackJackValue(int value, int totalCardValue)
{
	if (value > 1 && value <= 10)
		return value;
	else if (value > 10 && value < 14)
		return 10;
	return 0;
	/*
	else {
	if (totalCardValue == 10)
	return 11;
	else if ((11 + totalCardValue) > 21)
	return 1;
	else if (11 + totalCardValue == 21)
	return 11;
	else if ((1 + totalCardValue) < 11)
	return 11;
	}
	*/
	/*
	else if (value == 1) {
	if (totalCardValue == 10)
	return 11;
	else if (totalCardValue > 10)
	return 1;
	else {
	return 11;
	}
	}
	*/
}

void player1Turn()
{
	/*
	if (p1HasAce == true) {
	for (int i = 0; i < playerAces; i++) {
	//specialCaseAce();
	}
	p1CardValue += blackJackValue(player1[p1Size-1].getValue(), p1CardValue);
	}
	*/
	cout << "It is now your turn. The hand you have been dealt is: " << player1[0].displayCard() << ", " << player1[1].displayCard() << endl;
	cout << "Currently, your total card value is: " << p1CardValue << endl;
	cout << "The Dealer's Face-Up Card is: " << ai[1].displayCard() << endl;
	string theirChoice;
	bool okAnswer = false;
	while (okAnswer == false) {
		cout << "Type 'no' to stay, or 'yes' to hit" << endl;
		//cin.ignore(100);
		cin >> theirChoice;
		if (!(theirChoice == "no" || theirChoice == "yes")) {
			cout << "Please try again, that was an invalid answer." << endl;
		}
		else {
			okAnswer = true;
		}
	}
	//cppf: consider checking that their response is strictly 'yes' or 'no'. As it stands,
	//I can enter 'hi!' and have it react like I entered 'no'. Still playable, but could
	//be polished up a bit
	while (p1Size < 12 && theirChoice != "no")
	{
		player1[p1Size] = deck[topCard];
		topCard++;
		p1Size++;
		cout << p1Size << endl;
		cout << "You just received a " << deck[topCard - 1].displayCard() << endl;
		player1CardValue();
		/*
		if (p1HasAce == true) {
		/*
		for (int i = 0; i < playerAces; i++) {
		//specialCaseAce();
		}
		p1CardValue += blackJackValue(player1[p1Size-1].getValue(), p1CardValue);
		}
		*/
		cout << "Now your total card value is: " << p1CardValue << endl;
		if (p1CardValue > 21) {
			cout << "Ha! You busted! Sorry, better luck next time." << endl;
			busted = true;
			break;
		}
		else if (p1CardValue == 21) {
			cout << "Nice! You got 21!" << endl;
			break;
		}
		cout << "As a reminder - The Dealer's Face-Up Card is: " << ai[1].displayCard() << endl;
		okAnswer = false;
		while (okAnswer == false) {
			cout << "Type 'no' to stay, or 'yes' to hit" << endl;
			//cin.ignore(100);
			cin >> theirChoice;
			if (!(theirChoice == "no" || theirChoice == "yes")) {
				cout << "Please try again, that was an invalid answer." << endl;
			}
			else {
				okAnswer = true;
			}
		}
	}
}

/*
void normAITurn() {
while (aiCardValue <= 17) {
ai[aiSize] = deck[topCard];
topCard++;
aiSize++;
aiCV();
}
if (aiCardValue > 21) {
cout << "The dealer busted with " << aiCardValue << ". You win!" << endl;
}
else if (aiCardValue == 21) {
cout << "The dealer got BlackJack! Better luck next time." << endl;
}
else if (aiCardValue > p1CardValue) {
cout << "You lost to the dealer. You had " << p1CardValue << ", but the dealer has " << aiCardValue << "." << endl;
}
else if (p1CardValue > aiCardValue) {
cout << "You beat the dealer! He had " << aiCardValue << ", but you had " << p1CardValue << "." << endl;
}
else {
cout << "You tied with the dealer with " << p1CardValue << ", but the tie always goes to the dealer.  Better luck next time!" << endl;
}
}
*/

void aiTurn() {
	aiCV();
	while (aiCardValue < p1CardValue) {
		ai[aiSize] = deck[topCard];
		topCard++;
		aiSize++;
		aiCV();
		if (aiCardValue == p1CardValue)
			break;
	}

	if (aiCardValue > 21) {
		cout << "The dealer busted with " << aiCardValue << ". You win!" << endl;
		won = true;
	}
	else if (aiCardValue == 21) {
		cout << "The dealer got BlackJack! Better luck next time." << endl;
		won = false;
	}
	else if (aiCardValue > p1CardValue) {
		cout << "You lost to the dealer. You had " << p1CardValue << ", but the dealer has " << aiCardValue << "." << endl;
		won = false;
	}
	else if (p1CardValue > aiCardValue) {
		cout << "You beat the dealer! He had " << aiCardValue << ", but you had " << p1CardValue << "." << endl;
		won = true;
	}
	else {
		cout << "You tied with the dealer with " << p1CardValue << ", but the tie always goes to the dealer.  Better luck next time!" << endl;
		won = false;
	}
}

void player1CardValue()
{
	p1CardValue = 0;
	int len = p1Size;
	int aces = 0;
	for (int i = 0; i < len; i++) {
		if (player1[i].getValue() == 1)
		{
			for (int j = i + 1; j < p1Size; j++) {
				card temp = player1[i];
				player1[i] = player1[j];
				player1[j] = temp;
			}
			len--;
			aces++;
		}
		p1CardValue += blackJackValue(player1[i].getValue(), p1CardValue);
	}
	while (aces > 0){
		specialCaseAce();
		aces--;
	}
}

void aiCV() {
	aiCardValue = 0;
	int len = aiSize;
	int aces = 0;
	for (int i = 0; i < len; i++) {
		if (ai[i].getValue() == 1 || ai[i].getValue() == 14) {
			for (int j = i + 1; j < aiSize; j++) {
				card temp = ai[i];
				ai[i] = ai[j];
				ai[j] = temp;
			}
			len--;
			aces++;
		}
		aiCardValue += blackJackValue(ai[i].getValue(), aiCardValue);
	}
	while (aces > 0) {
		if (aiCardValue == 10)
			aiCardValue += 11;
		else if (aiCardValue > 10)
			aiCardValue += 1;
		else {
			aiCardValue += 11;
		}
		aces--;
	}
}



void specialCaseAce() {
	bool invalid = true;
	int aceValue = 0;
	while (invalid == true) {
		if (1 + p1CardValue > 21) {
			break;
		}
		cout << "It looks like you have an Ace. Would you like it to be valued at 1 or 11?" << endl;
		int sum = 0;
		for (int i = p1Size - 1; i >= 0; i--) {
			if (player1[i].getValue() != 1) {
				sum += blackJackValue(player1[i].getValue(), sum);
			}
		}
		cout << "For reference, if you added 1, the total would become: " << 1 + sum << endl;
		cout << "Or, if you added 11, the total would become: " << 11 + sum << endl;
		cin >> aceValue;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(100);
			cin >> aceValue;
		}
		if (aceValue == 1 || aceValue == 11)
			invalid = false;
		else if (roundEnded == true) {
			break;
		}
		else
			cout << "Please try again. You have entered an invalid number.";
	}
	p1CardValue += aceValue;
}

void displayAllCards() {
	cout << endl;
	cout << "The dealer's hand was: " << endl;
	for (int i = 0; i < aiSize; i++) {
		cout << ai[i].displayCard() << endl;
	}
	cout << "The dealer's hand totaled: " << aiCardValue << endl;
	cout << endl << "Your hand was: " << endl;
	for (int i = 0; i < p1Size; i++) {
		cout << player1[i].displayCard() << endl;
	}
	cout << "Your hand totaled: " << p1CardValue << endl;
}
