#include "GameBoard.h"
#include "Bin.h"
#include "util.h"
#include <memory>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iomanip>

struct GameBoard {
	unsigned num_colors;
	std::vector<UniqueBin> bins;
};

GameBoard* GameBoardCreate(unsigned numbins, unsigned height, unsigned colors) {
	assert (numbins != 0);
	assert (colors != 0);
	GameBoard * ret = new GameBoard;
	ret->num_colors = colors;
	for (unsigned i = 0; i < numbins; ++i) {
		//can't use resize as unique_ptr won't deep copy
		ret->bins.push_back(BinInstance(height));
	}
	GameBoardFill(ret);
	return ret;
}

void GameBoardDestroy(GameBoard* gb) {
	delete gb;
}

UniqueGameBoard GameBoardInstance(unsigned numbins, unsigned height, unsigned colors) {
	return UniqueGameBoard(GameBoardCreate(numbins, height, colors));
}

unsigned GameBoardWidth(Pointer<GameBoard> gb) {
	return gb->bins.size();
}

unsigned GameBoardHeight(Pointer<GameBoard> gb) {
	return BinHeight(gb->bins[0]);
}

element& GameBoardAt(Pointer<GameBoard> gb, unsigned bin, unsigned i) {
	return BinAt(gb->bins.at(bin), i);
}

//recursive function that marks all adjacent elements to
//GameBoardAt(gb, bin, i) of color as empty
static void mark_adjacent(Pointer<GameBoard> gb, unsigned bin, unsigned i, element color) {
	//Precondition: is_empty(GameBoardAt(gb, bin, i))
	element * new_color;
	//look left
	if (bin != 0 && color == *(new_color = &GameBoardAt(gb, bin-1, i))) {
		set_empty(*new_color);
		mark_adjacent(gb, bin-1, i, color);
	}
	//look down
	if (i != 0 && color == *(new_color = &GameBoardAt(gb, bin, i-1))) {
		set_empty(*new_color);
		mark_adjacent(gb, bin, i-1, color);
	}
	//look up
	if (i+1 < GameBoardHeight(gb) && color == *(new_color = &GameBoardAt(gb, bin, i+1))) {
		set_empty(*new_color);
		mark_adjacent(gb, bin, i+1, color);
	}
	//look right
	if (bin+1 < GameBoardWidth(gb) && color == *(new_color = &GameBoardAt(gb, bin+1, i))) {
		set_empty(*new_color);
		mark_adjacent(gb, bin+1, i, color);
	}
}
		

bool GameBoardMark(Pointer<GameBoard> gb, unsigned bin, unsigned i) {
	element& color = GameBoardAt(gb, bin, i);
	if (is_empty(color)) {
		return false; //invalid
	}
	//determine if adjacent element is of same color
	bool valid_mark = false;
	//use else as we only need one to be true so we know it's valid...
	if (bin != 0 && color == GameBoardAt(gb, bin-1, i)) {
		valid_mark = true;
	}
	else if (i != 0 && color == GameBoardAt(gb, bin, i-1)) {
		valid_mark = true;
	}
	else if (i+1 < GameBoardHeight(gb) && color == GameBoardAt(gb, bin, i+1)) {
		valid_mark = true;
	}
	else if (bin+1 < GameBoardWidth(gb) && color == GameBoardAt(gb, bin+1, i)) {
		valid_mark = true;
	}
	if (valid_mark) {
		element old_color = color;
		set_empty(color);
		mark_adjacent(gb, bin, i, old_color);
	}
	return valid_mark;
}

void GameBoardCollapse(Pointer<GameBoard> gb) {
	for (auto& bin : gb->bins) {
		BinCollapse(bin);
	}
	std::stable_sort(gb->bins.begin(), gb->bins.end(),
		[](const UniqueBin& a, const UniqueBin& b) {
			//a *must* sort before b if a is NOT empty and b is empty
			//(remember: this is operator<(), *not* operator<=()!
			return !BinEmpty(a) && BinEmpty(b);
		}
	);
}

void GameBoardPrint(Pointer<GameBoard> gb, std::ostream& os) {
	unsigned width = GameBoardWidth(gb);
	unsigned height = GameBoardHeight(gb);
	for (unsigned i = height; i != 0;) {
		os << std::setw(2) << i-- << ' '; //i-- to convert to start at 0
		for (unsigned j = 0; j < width; ++j) {
			os << ' ' << get_char(GameBoardAt(gb, j, i));
		}
		os << '\n';
	}
	os << "   "; //' '*(field width == 2) + ' '(for '|')
	for (unsigned j = 0; j < width; ++j) {
		os << " -";
	}
	os << "\n   ";
	for (unsigned char j = 'A'; j < 'A'+width; ++j) {
		os << ' ' << j;
	}
	os << std::endl; //now flush
}

void GameBoardFill(Pointer<GameBoard> gb) {
	for (auto& bin: gb->bins) {
		BinFill(bin, gb->num_colors);
	}
}
