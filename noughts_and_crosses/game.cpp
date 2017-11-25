#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#include "tictactoe.hpp"

using namespace std;


class PlayerException: public std::runtime_error {
public:
		PlayerException() : std::runtime_error("PlayerException") { }
};


class TokenException: public std::runtime_error {
public:
		TokenException() : std::runtime_error("TokenException") { }
};


class Player {
public:
	// constructor
	Player(const std::string& name_, char token_) {
		_name = name_;
		_token = token_;

		if (_token != 'o' && _token != 'x') {
			throw TokenException();	
		}
		if (_name.length() == 0) {
			throw PlayerException();
		}
	};

	std::string name() {
		return _name;
	}

	char token() {
		return _token;
	}

	long int score() {
		return _score;
	}

	void win() {
		_score = _score + 20;
	}

	void draw() {
		_score = _score + 10;
	}

	// redundant just added for completeness :-)
	void lose() {
		_score = _score + 0;
	}

	~Player() {};

	friend std::ostream& operator<<(std::ostream& out, Player& p_) {
		out << "[Name: " <<  p_.name() << ", ";
		out << "Token: " << p_.token() << ", ";
		out << "Score: " << p_.score() <<"]";
	}

private: 
	string _name = "";
	char _token = ' ';
	long int _score = 0;
};


// 
std::string ask_name(std::string& player);
char ask_token(std::string& player_);
char ask_yn(std::string& question_);
void play_a_game(int game_no, Player& p1, Player& p2);
void make_move(tictactoe::board& b, Player& p);
tictactoe::entry token_map(char token_);

int main() {
	const int number_of_players = 2;
	int game_no = 0;

	std::string n1 = "player 1";
	n1 = ask_name(n1);

	char t1;
	try {
		t1 = ask_token(n1);
	}
	catch (TokenException& e) {
		cout << "TokenException" << endl;
		exit(2);
	}
	

	Player p1 = Player(n1, t1);

	std::string n2 = "player 2";
	n2 = ask_name(n2);

	char t2 = ' ';
	if (t1 == 'o') {
		t2 = 'x';
	}
	else {
		t2 = 'o';
	}

	Player p2 = Player(n2, t2);

	bool game_in_progress = true;
	do {
		game_no++;

		// swap who starts first
		if (game_no % 2 == 1) {
			play_a_game(game_no, p1, p2);
		}
		else {
			play_a_game(game_no, p2, p1);
		}

		std::string another_go_question = "Do you want want another go (y/n)?";
		char ny = ask_yn(another_go_question);
	   if (ny == 'n') {
			game_in_progress = false;
		}
	} while(game_in_progress);

	if (p1.score() > p2.score()) {
		cout << p1.name();
		cout << " has won, well done!" << endl;
	}
	else if (p2.score() > p1.score()) {
		cout << p2.name();
		cout << " has won, well done!" << endl;
	} else {
		cout << "It's a draw!" << endl;
	}

	cout << p1 << endl;
	cout << p2 << endl;

	return 0;
}


std::string ask_name (std::string& player) {
	std::string name = "";

	std::cout << "What is your name " << player << "?" << std::endl;
	do {
		getline(std::cin, name);
	} while (name.length() == 0);

	return name;
}


char ask_token (std::string& player_) {
	char t;
	std::cin.clear();
	std::cout << "Please select a token " << player_ << " (o or x)?" << std::endl;
	do {
		t = getchar();
	} while (t != 'o' && t != 'x');

	if (t == 'o' or t == 'O') {
		return 'o';
	}
	else if (t == 'x' or t == 'X') {
		return 'x';
	}
	else {
		throw TokenException();
	}
}


// Play a single game of tictactoe
// inputs: 
//		game_no - the number of games played so far
//		p1 - player 1 the player going first this time around
//		p2 - player 2, the player going second  this time around
void play_a_game(int game_no, Player& p1, Player& p2) {
	std::cout << "Starting game " << game_no << endl;
	std::cout << "Player 1: " <<  p1 << std::endl;
	std::cout << "Player 2: " <<  p2 << std::endl;

	tictactoe::board b = tictactoe::board();	
	cout << b << endl;

	// We play until some one wins 
	// or until there are no more moves (a draw is then declared)
	int i = 1;
	bool in_play = true;
	while (in_play) {
		cout << "Move number " << i << endl;
		if (i % 2 == 0) {
			make_move(b, p1);
			cout << b << endl;
			tictactoe::entry t = token_map(p1.token());
			if (check_winner(b, t)) {
				p1.win();
				cout << p1 << " has won this game!" << endl;
				in_play = false;
			}
		}
		else {
			make_move(b, p2);
			cout << b << endl;
			tictactoe::entry t = token_map(p2.token());
			if (check_winner(b, t)) {
				p2.win();
				cout << p2 << " has won this game!" << endl;
				in_play = false;
			}
		}
		 
		if (check_draw(b)) {
			p1.draw();
			p2.draw();
			cout << " It's a draw!" << endl;
			in_play = false;
		}
		i++;
	}
}


// Ask a Yes / No question
// Only allow y or n as an answer
char ask_yn(std::string& question_) { 
	char yn = ' ';
	cout << question_ << endl;
	do {	
		yn = getchar();
	} while (yn != 'n' && yn != 'y');
}


void make_move(tictactoe::board& b, Player& p) {
	int r = -1;
	int c = -1; 

	std::string input;
	bool is_valid_move = false;

	// loop until we have a valid move
	do {
		// get move
		// get row
		do {
			std::cout << "Please select row " << p.name() << "?" << std::endl;
			cin >> input;
			r = input.at(0) - '0';
		} while (r < 0 || r > 2);

		// get column
		do {
			std::cout << "Please select column " << p.name() << "?" << std::endl;
			cin >> input;
			c = input.at(0) - '0';
		} while (c < 0 || c > 2);

		// check if valid move
		if (b(r, c) == tictactoe::entry::empty) {
			is_valid_move = true;
		}
		else {
			cout << "(" << r << "," << c << ") is an invalid move, please try again." << endl;
			is_valid_move = false;
		}
	} while (is_valid_move == false);

	// see comment for token_map
	b(r, c) = token_map(p.token());
}


// for convenience we have a function to
// map 'o' to tictactoe::entry::nought
// and 'x' to tictactoe::entry::cross
tictactoe::entry token_map(char token_) {
	if (token_ == 'o') {
		return tictactoe::entry::nought;
	}
	else if (token_ == 'x') {
		return tictactoe::entry::cross;
	}
	else {
		throw TokenException();
	}
}
