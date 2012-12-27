#include "Bin.h"
#include "element.h"
#include "util.h"
#include <cassert>
#include <memory>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct Bin {
	std::vector<element> elems;
};

Bin * BinCreate(unsigned height) {
	assert (height != 0);
	Bin * ret = new Bin;
	ret->elems.resize(height);
	return ret;
}

Bin * BinCreate(Pointer<Bin> other) {
	assert (other);
	Bin * ret = new Bin;
	*ret = *other; //default copy ctor should work
	return ret;
}

void BinDestroy(Bin* bin) {
	delete bin;
}

UniqueBin BinInstance(unsigned height) {
	return UniqueBin(BinCreate(height));
}

UniqueBin BinInstance(Pointer<Bin> other) {
	return UniqueBin(BinCreate(other));
}

void BinCollapse(Pointer<Bin> bin) {
	//should be O(NlogN) as we shouldn't run out of memory...
	std::stable_sort(bin->elems.begin(), bin->elems.end(),
		[](const element& a, const element& b) {
			//a *must* sort before b if a is NOT empty and b is empty
			//(remember: this is operator<(), *not* operator<=()!
			return !is_empty(a) && is_empty(b);
		}
	); //gotta love the standard library...
}

unsigned BinHeight(Pointer<Bin> bin) {
	return bin->elems.size();
}

element& BinAt(Pointer<Bin> bin, unsigned i) {
	return bin->elems.at(i); //bounds checked
}

bool BinEmpty(Pointer<Bin> bin) {
	bool empty = true;
	for (auto& elem : bin->elems) {
		if (!is_empty(elem)) {
			empty = false;
			break;
		}
	}
	return empty;
}

void BinFill(Pointer<Bin> bin, unsigned numcolors) {
	static bool init = false;
	if (!init) {
		std::srand(std::time(nullptr));
		init = true;
	}
	for (auto& elem: bin->elems) {
		elem = std::rand() % numcolors;
	}
}
		
