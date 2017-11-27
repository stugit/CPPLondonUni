#include <iostream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

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


TEST (PlayerTest, ScoreStartsZero)
{
	Player p1 = Player("Spiderman", 'o');
	EXPECT_EQ(0, p1.score());
}

TEST (PlayerTest, TokenIsO)
{
	Player p1 = Player("Batman", 'o');
	EXPECT_EQ('o', p1.token());
}

TEST (PlayerTest, IAMBATMAN)
{
	Player p1 = Player("Batman", 'o');
	EXPECT_EQ("Batman", p1.name());
}

TEST (PlayerTest, IAMNOTBATMAN)
{
	Player p1 = Player("Superman", 'o');
	EXPECT_NE("Batman", p1.name());
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	return 0;
}
