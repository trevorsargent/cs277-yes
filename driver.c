#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include <math.h>

int main(int argc, char *argv[]){
	//see notes.md for structure of hardware array
	int* hardware = malloc(sizeof(int) * 12);
	unsigned char* memory = malloc(sizeof(char) * pow(2,19));

	int stackBottom = readFile(argc, argv, memory);
	return 0;
}