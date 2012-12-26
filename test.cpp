#include "util.h"
#include <memory>
#include <iostream>

void foo(Pointer<int> x) {
	std::cout << *x << std::endl;
}

int main() {
	int x = 5;
	std::unique_ptr<int> p(new int(5));
	foo(&x);
	foo(p);
	return 0;
}

