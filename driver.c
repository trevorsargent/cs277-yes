#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tools.h"
#include "codes.h"
#include "instruct.h"

void instruct(unsigned char instruction, unsigned char *memory, int * chip);

int main(int argc, char *argv[]){

	// see notes.md for structure of chip array
	int* chip = (int*)malloc(sizeof(int) * CHIP_SZ);

	// create main memory
	unsigned char* memory = (unsigned char*)malloc(sizeof(char) * MEM_SZ);

	// read in file
	chipWrite(chip, SEG, readFile(argc, argv, memory));

	// set up the rest of the pointers
	chipSetup(chip);
	
	// Sequential Execution
	unsigned char instruction;
	do{
		// read the byte at the PC's position
		instruction = memRead(memory, chip, chipRead(chip, PC));

		// throw error if any reading was not completed correctly
		if(chipRead(chip, STAT)!=AOK){
			break;
		}

		// execute the instruction: full instruction cycle
		instruct(instruction, memory, chip);
		
	}while(chipRead(chip, STAT) == AOK);

	// print visible statue of system at halt. 
	printState(chip);
	return 0;
}

void instruct(unsigned char instruction, unsigned char *memory, int * chip){
	// extract the icode and ifun from the 
	unsigned char icode = (instruction>>4)&0x0F;
	unsigned char ifun = instruction&0x0F;

	// branch based on icode
	switch(icode){
		
		case 0x0:
			halt(chip, ifun);
			break;
		case 0x1:
			noop(chip, ifun);
			break;
		case 0x2:
			rrmovl(memory, chip, ifun);
			break;
		case 0x3:
			irmovl(memory, chip, ifun);
			break;
		case 0x4:
			rmmovl(memory, chip, ifun);
			break;
		case 0x5:
			mrmovl(memory, chip, ifun);
			break;
		case 0x6:
			op(memory, chip, ifun);
			break;
		case 0x7:
			jmp(memory, chip, ifun);
			break;
		case 0x8:
			call(memory, chip, ifun);
			break;
		case 0x9:
			ret(memory, chip, ifun);
			break;
		case 0xA:
			push(memory, chip, ifun); 
			break;
		case 0xB:
			pop(memory, chip, ifun);
			break;	
		default:
			chipWrite(chip, STAT, INVIN);
			return;
				
	}
	// increment the PC based on the instruction
	pincrement(chip, instructionLength(icode));

	// update the number of instructions executed
	chipWrite(chip, NUMOPS, chipRead(chip, NUMOPS) +1);

	return;

}
