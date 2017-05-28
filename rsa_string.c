#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_ARGUMENTS			-1
#define FILE_ERROR_INPUT			-2
#define FILE_ERROR_OUTPUT			-3
#define MEMORY_ALLOCATION_ERROR		-4
#define FILE_READING_ERROR			-5

union Input{
	char *plain_input;
	double *cypher_input;
} input;

union Output{
	char *plain_output;
	double *cypher_output;
} output;

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
	FILE *input_file;
	FILE *output_file;
	//Abre arquivos
	if(mode == 'e'){ //modo de criptografar
		input_file = fopen(argv[2], "r");
		if(input_file == NULL){
			printf("ERROR: Failure in opening file.\n");
			return FILE_ERROR_INPUT;
		}
		output_file = fopen(argv[3], "w");
		if(output_file == NULL){
			printf("ERROR: Failure in opening file.\n");
			return FILE_ERROR_OUTPUT;
		}
	}
	else{	//modo de decriptografar
		input_file = fopen(argv[2], "r");
		if(input_file == NULL){
			printf("ERROR: Failure in opening file.\n");
			return FILE_ERROR_INPUT;
		}
		output_file = fopen(argv[3], "w");
		if(output_file == NULL){
			printf("ERROR: Failure in opening file.\n");
			return FILE_ERROR_OUTPUT;
		}
	}


	long f_size;
	union Input input;
	union Output output;
	size_t result;
	int cont;
	fseek(input_file, 0, SEEK_END);
	f_size = ftell(input_file);
	printf("FILE SIZE %d\n", f_size);
	rewind(input_file);
	printf("mode %c\n", mode);
	printf("TESTE 1\n");
	if(mode == 'e'){
		printf("ENCRYPTING\n");
		input.plain_input = (char*)malloc(f_size*sizeof(char));
		if(input.plain_input == NULL){
			printf("ERROR: Insuficient memory.\n");
			fclose(input_file);
			fclose(output_file);
			return MEMORY_ALLOCATION_ERROR;
		}

		result = fread(input.plain_input, 1, f_size, input_file);
		if(result != f_size){
			printf("ERROR: Failed reading file.\n");
			fclose(input_file);
			fclose(output_file);
			return FILE_READING_ERROR;
		}

	}
	else{
		input.plain_input = (char*)malloc(f_size*sizeof(char));
		if(input.plain_input == NULL){
			printf("ERROR: Insuficient memory.\n");
			fclose(input_file);
			fclose(output_file);
			return MEMORY_ALLOCATION_ERROR;
		}
		//wesley -- problema aqui
		printf("DECRYPTING\n");
		result = fread(input.plain_input, 1, f_size, input_file);
		if(result == 0){
			printf("ERROR: Failed reading file.\n");
			fclose(input_file);
			fclose(output_file);
			return FILE_READING_ERROR;
		}
			input.plain_input[f_size-1] = '\0';
			printf("%s\n", input.plain_input);
			printf("%c -- %d\n", input.plain_input[f_size-1], input.plain_input[f_size-1]);

			//scanf("%s\n", &cont);
	}
	printf("OUT\n");
	printf("input_size %d\n", result);
	//scanf("%s\n", &cont);


	// Logica RSA
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
	//void *cyphertext;
	if(mode == 'e'){
		/*cyphertext = (double *)malloc(sizeof(double)*f_size);
		if(cyphertext == NULL){
			printf("ERROR: Insuficient memory.\n");
			fclose(input_file);
			fclose(output_file);
			free(input);
			return MEMORY_ALLOCATION_ERROR;
		}*/
		char tmp[10000];
		char print[10000];
		output.cypher_output = (double *)malloc(sizeof(double)*f_size);
		if(output.cypher_output == NULL){
			printf("ERROR: Insuficient memory.\n");
			fclose(input_file);
			fclose(output_file);
			free(input.plain_input);
			return MEMORY_ALLOCATION_ERROR;
		}
		for(i=0;i<f_size;i++){
		//	input[0] -= 65;
			output.cypher_output[i] = pow(input.plain_input[i], e);
			output.cypher_output[i] = fmod(output.cypher_output[i], n);
		}
		printf("f_size %lf\n", f_size);
		printf("c_size %lf\n", sizeof(output.cypher_output));
		printf("i %d\n", i);
		for(;i>0;i--){
			printf("%lf\n", output.cypher_output[f_size-i]);
		}
		for(i=0;i<f_size;i++){
			sprintf(tmp, "%lf", output.cypher_output[i]);
			strcat(print, tmp);
			if(i != f_size-1){
				strcat(print, " ");
			}
		}
		fprintf(output_file, "%s", print);
		/*
		result = fwrite(output.cypher_output, sizeof(double), f_size, output_file);
		if(result == 0){
			printf("ERROR: Failed to write file\n");
		}*/
		printf("encrypt_size %d\n", result);

	}
	else{	//Decripta
	/*	cyphertext = (char *)malloc(sizeof(char)*f_size);
		if(cyphertext == NULL){
			printf("ERROR: Insuficient memory.\n");
			fclose(input_file);
			fclose(output_file);
			free(input);
			return MEMORY_ALLOCATION_ERROR;
		}*/
		for(;i>0;i--){
			printf("%lf\n", input.plain_input[f_size-i]);
		}
		output.plain_output = (char *)malloc(sizeof(char)*f_size);
		if(output.plain_output == NULL){
			printf("ERROR: Insuficient memory.\n");
			fclose(input_file);
			fclose(output_file);
			free(input.plain_input);
			return MEMORY_ALLOCATION_ERROR;
		}
		for(i=0;i<f_size;i++){
			//TO-DO
			output.plain_output[i] = pow(input.plain_input[i], d);
			output.plain_output[i] = fmod(output.plain_output[i], n);
		}

		for(i=0;i<f_size;i++){
			printf("%c\n", output.plain_output[i]);
		}
		result = fwrite(output.plain_output, sizeof(char), f_size, output_file);
		if(result == 0){
			printf("ERROR: Failed to write file\n");
		}
		printf("decrypt_size %d\n", result);
	}

	//Tira o lixo pra fora
	fclose(input_file);
	fclose(output_file);
	if(mode == 'e'){
		free(input.plain_input);
		free(output.cypher_output);
	}
	else{
		free(input.plain_input);
		free(output.plain_output);
	}


	return 0;
}
