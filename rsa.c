#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_ARGUMENTS			-1
#define FILE_ERROR_INPUT			-2
#define FILE_ERROR_OUTPUT			-3
#define MEMORY_ALLOCATION_ERROR		-4
#define FILE_READING_ERROR			-5

int mdc(int a, int b){
	if(a == 0){
		return 0;
	}
	return mdc(a%b, a);
}

/* Random Prime Numbers
1467511
8101127
*/
typedef unsigned long long ulint;
/* Usage
	prog [mode] [input_path] [output_path]
	mode = e (encrypt)
		   d (decrypt)
*/
int main(int argc, char const *argv[]) {
	//Verifica argumentos
	if(argc != 4){
		printf("ERROR: Invalid number of arguments.\n");
		return INVALID_ARGUMENTS;
	}
	int i;
	if(!(strcmp(argv[1], "e")) && !(strcmp(argv[1], "d"))){
		printf("ERROR: Invalid mode.\n");
		return INVALID_ARGUMENTS;
	}

	char mode = argv[1][0];

	//Abre arquivos

	FILE *input_file = fopen(argv[2], "r");
	if(input_file == NULL){
		printf("ERROR: Failure in opening file.\n");
		return FILE_ERROR_INPUT;
	}
	FILE *output_file = fopen(argv[3], "w");
	if(output_file == NULL){
		printf("ERROR: Failure in opening file.\n");
		return FILE_ERROR_OUTPUT;
	}
	long f_size;
	char *input;
	char *output;
	size_t result;

	fseek(input_file, 0, SEEK_END);
	f_size = ftell(input_file);
	rewind(input_file);

	input = (char*)malloc(f_size*sizeof(char));
	if(input == NULL){
		printf("ERROR: Insuficient memory.\n");
		fclose(input_file);
		fclose(output_file);
		return MEMORY_ALLOCATION_ERROR;
	}
	result = fread(input, 1, f_size, input_file);
	if(result != f_size){
		printf("ERROR: Failed reading file.\n");
		fclose(input_file);
		fclose(output_file);
		return FILE_READING_ERROR;
	}
	printf("res %d\n", (int)result);


	// Logica RSA
	ulint private_k;
	/*
	ulint q = 1467511;
	ulint p = 8101127;
*/
	ulint p = 3;
	ulint q = 7;
	//Chave pública
	ulint n = p * q;
	//Chave Privada
	long double d;

	ulint phi = (p-1)*(q-1);
	ulint e = 2;
	ulint k = 2;
	while (e < phi) {
		if(mdc(e, phi) == 1)
			break;
		else
			e++;
	}
	d = (1+(k*phi))/e;

	//Encripta
	double *cyphertext = (double *)malloc(sizeof(double)*f_size);
	if(cyphertext == NULL){
		printf("ERROR: Insuficient memory.\n");
		return MEMORY_ALLOCATION_ERROR;
	}
	if(mode == 'e'){
		for(i=0;i<f_size;i++){
		//	input[0] -= 65;
			cyphertext[i] = pow(input[i], e);
			cyphertext[i] = fmod(cyphertext[i], n);
		}
		for(i=0;i<6;i++)
		printf("%lf\n", cyphertext[i]);
	}
	else{	//Decripta
		for(i=0;i<f_size;i++){
			//TO-DO
			cyphertext[i] = pow(input[i], e);
			cyphertext[i] = fmod(cyphertext[i], n);
		}
	}

	//Tira o lixo pra fora
	fclose(input_file);
	fclose(output_file);
	free(input);
	free(output);
	free(cyphertext);
	return 0;
}
