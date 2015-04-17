#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include <math.h>

int main(int argc, char *argv[]){

	// see notes.md for structure of chip array
	int* chip = malloc(sizeof(int) * 12);

	// main memory
	unsigned char* memory = malloc(sizeof(char) * pow(2,19));

	// read in file
	int stackBottom = readFile(argc, argv, memory);

	//something else

	return 0;
}