//
// Created by Tristan Brindle on 14/11/2017.
//

#include "tictactoe.hpp"

namespace tictactoe {

std::ostream& operator<<(std::ostream& os, entry e)
{
    switch (e) {
    case entry::empty:
        return os << " ";
    case entry::nought:
        return os << "O";
    case entry::cross:
        return os << "X";
    }
}

board::board()
{
    array_.fill(entry::empty);
}

entry board::operator()(int row, int col) const
{
    if (row < 0 || row > 2) {
        throw std::out_of_range{
                "Row must be in the range 0-2, got " + std::to_string(row)};
    }
    if (col < 0 || col > 2) {
        throw std::out_of_range{
                "Column must be in the range 0-2, got " + std::to_string(col)};
    }

    return array_[row * 3 + col];
}

entry& board::operator()(int row, int col)
{
    if (row < 0 || row > 2) {
        throw std::out_of_range{
                "Row must be in the range 0-2, got " + std::to_string(row)};
    }
    if (col < 0 || col > 2) {
        throw std::out_of_range{
                "Column must be in the range 0-2, got " + std::to_string(col)};
    }

    return array_[row * 3 + col];
}

std::ostream& operator<<(std::ostream& os, const board& b)
{
    os << "\n";
    os << " " << b(0, 0) << " | " << b(0, 1) << " | " << b(0, 2) << "\n";
    os << "---+---+---\n";
    os << " " << b(1, 0) << " | " << b(1, 1) << " | " << b(1, 2) << "\n";
    os << "---+---+---\n";
    os << " " << b(2, 0) << " | " << b(2, 1) << " | " << b(2, 2) << "\n\n";
    return os;
}

// TODO: Implement this function correctly
bool check_winner(const board& b, entry e)
{
	int count = 0;
	// check rows
	for (int r=0; r<3; r++) {
		count = 0;
		for (int c=0; c<3; c++) {
			if (b(r, c) == e) {
				count++;
			}
			if (count == 3) {
				return true;
			}
		}
	}

	// check columns
	for (int c=0; c<3; c++) {
		count = 0;
		for (int r=0; r<3; r++) {
			if (b(r, c) == e) {
				count++;
			}
			if (count == 3) {
				return true;
			}
		}
	}

	// check diagonals
	if (b(0,0) == e && b(1,1) == e && b(2,2) == e) {
		return true;
	}

	if (b(0,2) == e && b(1,1) == e && b(2,0) == e) {
		return true;
	}

    return false;
}

// TODO: Implement this function correctly
// If no more available moves and no one has won it must be a draw.
bool check_draw(const board& b)
{
	// count empties
	int count = 0;
	for (int r=0; r<3; r++) {
		for (int c=0; c<3; c++) {
			if (b(r, c) == tictactoe::entry::empty) {
				return false;
			}
		}
	}

    return true;
}



}
