#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tools.h"
#include "codes.h"

int main(int argc, char *argv[]){

	// see notes.md for structure of chip array
	int* chip = (int*)malloc(sizeof(int) * CHIP_SZ);

	// create main memory
	unsigned char* memory = (unsigned char*)malloc(sizeof(char) * MEM_SZ);

	// read in file
	chipWrite(chip, SEG, readFile(argc, argv, memory));

	//set up the rest of the pointers
	chipWrite(chip, EBP, MAXMEM);
	chipWrite(chip, ESP, MAXMEM);
	chipWrite(chip, PC,  0x0);
	
	//something else

	return 0;
}