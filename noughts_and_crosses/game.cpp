#include <iostream>
#include <string>
#include <sstream>

#include "tictactoe.hpp"

using namespace std;

class Player {
public:
	// constructor
	Player(const std::string& name_): score(0) {
		_name = name_;
	};
	std::string as_string() {
		return _name;
	}
	~Player() {};

private: 
	string _name;
	long int score;
};

std::string ask_name(std::string player);
void play_a_game(Player& p1, Player& p2);

int main() {
	const int number_of_players = 2;
	int game_no = 0;

	std::string n1 = "player 1";
	n1 = ask_name(n1);

	Player p1 = Player(n1);
	std::cout << "Player 1: " <<  p1.as_string() << std::endl;

	std::string n2 = "player 2";
	n2 = ask_name(n2);

	Player p2 = Player(n2);
	std::cout << "Player 2: " <<  p2.as_string() << std::endl;

	play_a_game(p1, p2);
	return 0;
}

std::string ask_name (std::string player) {
	std::string name = "";

	do {
		std::cout << "What is your name " << player << "?" << std::endl;
		getline(std::cin, name);
	} while (name.length() == 0);

	return name;
}

void play_a_game(Player& p1, Player& p2) {
	tictactoe::board b = tictactoe::board();	
	cout << b << endl;
	
	bool game_end = false;
	while () {
	}
}
