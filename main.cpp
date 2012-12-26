#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <array>
#include "GameBoard.h"
#include "difficulty.h"
#include "util.h"

const difficulty& get_difficulty() {
	for (unsigned i = 1; i <= sizeof(levels)/sizeof(levels[0]); ++i) {
		std::cout << i << ". " << levels[i-1].tag << '\n';
	}
	unsigned level;
	for (bool has_difficulty = false; !has_difficulty;) {
		std::cout << "> ";
		std::cin >> level;
		if (level != 0 && level <= sizeof(levels)/sizeof(levels[0])) {
			has_difficulty = true;
			std::cout << "Level " << level;
			--level; //bring level to count from 0
			std::cout << "\n- Rows:   " << levels[level].numrows;
			std::cout << "\n- Cols:   " << levels[level].numcols;
			std::cout << "\n- Colors: " << levels[level].numcolors << "\n\n";
		}
		else {
			std::cout << "Invalid level.\n";
		}
	}
	return levels[level];
}

std::array<unsigned, 2> get_move(unsigned numrows, unsigned numcols) {
	unsigned row, col;
	for (bool hasmove = false; !hasmove;) {
		std::cout << "Your move: ";
		std::string move;
		std::cin >> move;
		if (std::isupper(move[0])) {
			col = move[0] - 'A';
			move.erase(0, 1); //erase the alpha character
			if (std::isdigit(move[0])) {
				//need this check to avoid leading +/- accepted by atoi
				row = (unsigned) atoi(move.c_str());
				if (row != 0) {
					//if row == 0 input is invalid or 0 (which is out of range)
					--row; //so that we'll count from 0
					if (row < numrows && col < numcols) {
						//in range
						hasmove = true;
					}
				}
			}
		}
		if (!hasmove) {
			std::cout << "Invalid move.\n";
		}
	}
	return std::array<unsigned, 2>{{row, col}};
}

bool valid_move(Pointer<GameBoard> board) {
	return true; //TODO
}	

int main() {
	auto level = get_difficulty();
	auto board = GameBoardInstance(level.numcols, level.numrows, level.numcolors);
	while (valid_move(board)) {
		GameBoardPrint(board, std::cout);
		for (bool good_move = false; !good_move;) {
			auto move = get_move(level.numrows, level.numcols);
			good_move = GameBoardMark(board, move[1], move[0]);
			if (!good_move) {
				std::cout << "Invalid move.\n";
			}
		}
		GameBoardCollapse(board);
	}
	return 0;
}
