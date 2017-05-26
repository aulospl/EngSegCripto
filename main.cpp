#include "cripto.h"
#include <iostream>
#include <cstdlib>

#define NUMBER_ARGUMENTS 2Doc
#define NEW_ERROR -1
#define ARGUMENTS_ERROR -2

int main(int argc, char const *argv[]) {
	if(argc != NUMBER_ARGUMENTS){
		std::cout << "Error: Invalid number of arguments" << '\n';
		return ARGUMENTS_ERROR;
	}
	Cripto *c = new Cripto(atoi(argv[1]));
	if(c == NULL){
		std::cout << "Error: failed to instantiate cryptography" << '\n';
		return NEW_ERROR;
	}
	std::cout << c->getA() << '\n';
	delete(c);
	return 0;
}
