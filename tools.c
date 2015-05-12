#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "codes.h"

//returns the 8 bits of the binary representation of the 2 digit hex value passed: 
//'A','B' -> 0xAB 
unsigned char hexConvert(char a, char b){
	int i =0;
	unsigned char ret = 0x00;
	if(a >= 'a' && a <= 'f'){
		ret += a - 'a' + 0xA;
	}else if(a >= '0' && a <= '9'){
		ret += a - '0';
	}
	ret = ret << 4;
	if(b >= 'a' && b <= 'f'){
		ret += b - 'a' + 0xA;
	}else if(b >= '0' && b <= '9'){
		ret += b - '0';
	}
	return ret;
}

int readFile(int argc, char * argv[], unsigned char * memory){

	if(argc > 2){
		puts("Error: More than 1 executable supplied.");
		exit(0);
	}else if(argc < 2){
		puts("Welcome to YES, a y86 virtual machine. Please re-run, and supply a .yo executable on the command line.");
		exit(0);
	}

	FILE *fp = fopen(argv[1], "r");
	if(fp == 0){
		printf("Error: Could not open file <%s>\n",argv[1]);
		exit(0);
	}

	//puts("Status: Reading file");

	int i = 0x0;

	do{
		char a = fgetc(fp);
		char b = fgetc(fp);
		//fgetc(fp);
		*(memory + i) = hexConvert(a, b);
		i++;
	}while(!feof(fp) && !ferror(fp));
	
	return i;
}

int memRead(unsigned char* memory, int* chip, int address){
	if(address > MAXMEM){
		chipWrite(chip, STAT, INVAD);
		//printf("INVALID READ\n");
		return 0;
	}else{
		chipWrite(chip, STAT, AOK);
		return *(memory + address);
	}
}

int memWrite(unsigned char* memory, int* chip, int address, int value){
	if(address > MAXMEM || address < chipRead(chip, SEG)){
		chipWrite(chip, STAT, INVAD);
		
		return 0;
	}else{
		int i;
		for(i=0; i<4; i++){
			*(memory + address + i) = ((value >> 8*i) & 0xff);
		}
		chipWrite(chip, STAT, AOK);
		return 1;
	}
}

int chipRead(int* chip, int reg){
	if(reg >= EAX && reg <= NUMOPS){
		return *(chip+reg);
	}
	int stat = (*(chip+CC) >> 3) & 0x3;
	switch (reg){
		case CZ:
			return (*(chip + CC) & 0x1);
		case  CS:
			return (*(chip+CC) >> 1) & 0x01;
		case CO:
			return (*(chip+CC) >>2) & 0x01;
		case STAT: 
			switch (stat){
				case 0: return AOK;
				case 1: return HALT;
				case 2: return INVAD;
				case 3: return INVIN; 
			}	
	}
	return 0;
}

int chipWrite(int* chip, int reg, int value){
	if(reg >= EAX && reg <= NUMOPS){
		*(chip+reg) = value;
	}
	switch (reg){
		case CZ:
			*(chip + CC)= value & 0x01;
			return 1;
		case  CS:
			*(chip + CC) = (value & 0x01) << 1;
			return 1;
		case CO:
			*(chip + CC) = (value & 0x01) << 2;
			return 1;
		case STAT:
			*(chip+CC) &= 0x7; //set the bits for this flag to zero no matter what, 
			switch (value){
				case AOK: 
					return 1; //set to 0 (done already)
				case HALT: *(chip+CC) |= 0x8; //set them to the pre-shiftefd value of 01
					return 1;
				case INVAD: *(chip+CC) |= 0x10; //preshifted 10
					return 1;
				case INVIN: *(chip+CC) |= 0x18; //preshifted 11
					return 1;
			}	
			return 0;
	}
	return 0;
}

int littleEndianInt(unsigned char* memory, int* chip, int lowest){
	int ret = 0;
	ret |= (int)memRead(memory, chip, lowest);
	ret |= (((int)memRead(memory, chip, lowest+1))<<8);
	ret |= (((int)memRead(memory, chip, lowest+2))<<16);
	ret |= (((int)memRead(memory, chip, lowest+3))<<24);
	return ret;
}

/*
int bigEndianInt(unsigned char* memory, int* chip, int highest){
	int ret = 0;
	ret |= (int)memRead(memory, chip, highest);
	ret |= (((int)memRead(memory, chip, highest-1))<<8);
	ret |= (((int)memRead(memory, chip, highest-2))<<16);
	ret |= (((int)memRead(memory, chip, highest-3))<<24);
	return ret;
}
*/

int instructionLength(int icode){
	switch(icode){
		case 0x0: return 1;
		case 0x1: return 1;
		case 0x2: return 2;
		case 0x3: return 6;
		case 0x4: return 6;
		case 0x5: return 6;
		case 0x6: return 2;
		case 0x7: return 5;
		case 0x8: return 5;
		case 0x9: return 1;
		case 0xA: return 2;
		case 0xB: return 2;
		default: return 0;	
	}
}

void printState(int* chip){
	
	printf("Steps: %d\n", chipRead(chip, NUMOPS));
	printf("PC: 0x%08x\n", chipRead(chip, PC));
	printf("Status: ");
	switch(chipRead(chip, STAT)){
		case AOK : printf("AOK\n"); break;
		case HALT: printf("HALT\n"); break;
		case INVAD: printf("INVAD\n"); break;
		case INVIN: printf("INVIN\n"); break;
	}

	printf("CZ: %d\n", chipRead(chip, CZ));
	printf("CS: %d\n", chipRead(chip, CS));
	printf("CO: %d\n", chipRead(chip, CO));

	printf("EAX: 0x%08x\n", chipRead(chip, EAX));
	printf("ECX: 0x%08x\n", chipRead(chip, ECX));
	printf("EDX: 0x%08x\n", chipRead(chip, EDX));
	printf("EBX: 0x%08x\n", chipRead(chip, EBX));
	printf("ESP: 0x%08x\n", chipRead(chip, ESP));
	printf("EBP: 0x%08x\n", chipRead(chip, EBP));
	printf("ESI: 0x%08x\n", chipRead(chip, ESI));
	printf("EDI: 0x%08x\n", chipRead(chip, EDI));

}

void chipSetup(int* chip){
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

	chipWrite(chip, CZ, 0);
	chipWrite(chip, CS, 0);
	chipWrite(chip, CO, 0);
}

void pincrement(int* chip, int length){
	chipWrite(chip, PC, chipRead(chip, PC) + length);
}




