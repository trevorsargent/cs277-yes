#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tools.h"
#include "codes.h"
#include "driver.h"
#include "instruct.h"


int main(int argc, char *argv[]){

	// see notes.md for structure of chip array
	int* chip = (int*)malloc(sizeof(int) * CHIP_SZ);

	// create main memory
	unsigned char* memory = (unsigned char*)malloc(sizeof(char) * MEM_SZ);

	// read in file
	chipWrite(chip, SEG, readFile(argc, argv, memory));

	//set up the rest of the pointers
	chipSetup(chip);
	
	//Sequential Execution
	unsigned char instruction;
	do{
		//read the byte at the PC's position
		instruction = memRead(memory, chip, chipRead(chip, PC));

		//throw error if any reading was not completed correctly
		if(chipRead(chip, STAT)!=AOK){
			break;
		}

		instruct(instruction, memory, chip);
		
	}while(chipRead(chip, STAT) == AOK);

	printState(chip);
	return 0;
}

void instruct(unsigned char instruction, unsigned char *memory, int * chip){
	unsigned char ifun = instruction&0x0F;
	unsigned char icode = (instruction>>4)&0x0F;
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
	pincrement(chip, instructionLength(icode));
	chipWrite(chip, NUMOPS, chipRead(chip, NUMOPS) +1);
	return;

}
