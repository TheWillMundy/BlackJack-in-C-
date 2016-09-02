#include <string>
using namespace std;

class card
{
private:
	int value;
	string suit;

public:
	card() {
		value = 1;
		suit = 'S';
	}
	card(int val, string s) {
		value = val;
		suit = s;
	}

	int getValue() {
		return value;
	}

	string getSuit() {
		return suit;
	}

	void setValue(int val) {
		value = val;
	}

	string displayCard() {
		string display = "The ";
		switch (value) {
		case 1:
			display += "Ace of ";
			break;
		case 2 - 10:
			display += to_string(value);
			display += " of ";
			break;
		case 11:
			display += "Joker of ";
			break;
		case 12:
			display += "Queen of ";
			break;
		case 13:
			display += "King of ";
			break;
		case 14:
			display += "Ace of ";
			break;
		default:
			display += to_string(value);
			display += " of ";
			break;
		}
		display += suit;
		return display;
	}
};