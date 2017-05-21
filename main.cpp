#include "cripto.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char const *argv[]) {
	Cripto *c = new Cripto(atoi(argv[1]));
	std::cout << c->getA() << '\n';
	delete(c);
	return 0;
}
