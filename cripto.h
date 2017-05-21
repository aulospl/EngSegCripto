#ifndef _cripto_h
#define _cripto_h

#include <string>
#include <cstdio>

class Cripto {
private:
	std::string key;
	FILE *file;
	int a;


public:
	Cripto(int a);
	FILE * encrypt(FILE *input, std::string key);
	FILE * decrypt(FILE *input, std::string key);
	int getA();
};


#endif
