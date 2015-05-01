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
	chipWrite(chip, NUMOPS, 0);
	chipWrite(chip, STAT, AOK);

	chipWrite(chip, EAX, 0);
	chipWrite(chip, ECX, 0);
	chipWrite(chip, EDX, 0);
	chipWrite(chip, EBX, 0);
	chipWrite(chip, ESI, 0);
	chipWrite(chip, EDI, 0);

	
	//something else

	printState(chip);
	return 0;
}