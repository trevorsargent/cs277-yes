#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

//returns the 8 bits of the binary representation of the 2 digit hex value passed: 
//'A','B' -> 0xAB 
unsigned char hexConvert(char a, char b){
	int i =0;
	unsigned char ret = 0x00;
	if(a >= 'A' && a <= 'F'){
		ret += a - 'A' + 0xA;
	}else if(a >= '0' && a <= '9'){
		ret += a - '0';
	}
	ret = ret << 4;
	if(b >= 'A' && b <= 'F'){
		ret += b - 'A' + 0xA;
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

	puts("Status: Reading file");

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

int memRead(unsigned char* memory, int* chip, int address, unsigned char* ret){
	if(address > MAXMEM){
		chipWrite(chip, STAT, INVAD);
		return 0;
	}else{
		*ret = *(memory + address);
		return 1;
	}
}

int memWrite(unsigned char* memory, int* chip, int address, unsigned char value){
	return 0;
}

int chipRead(int* chip, int reg, int* ret){

	if(reg >= EAX && reg <= SEG){
		*ret = *(chip+reg);
	}
	int stat = (*(chip+CC) >> 3) & 0x3;
	switch (reg){
		case ZF:
			*ret = (*(chip + CC) & 0x1);
			return 1;
		case  SF:
			*ret = (*(chip+CC) >> 1) & 0x01;
			return 1;
		case OF:
			*ret = (*(chip+CC) >>2) & 0x01;
			return 1;
		case STAT: 
			switch (stat){
				case 0: *ret = AOK;
					return 1;
				case 1: *ret = HALT;
					return 1;
				case 2: *ret = INVAD;
					return 1;
				case 3: *ret = INVIN; 
					return 1;
			}	
			return 0;

	}
	return 0;
}

int chipWrite(int* chip, int reg, int value){
	if(reg >= EAX && reg <= SEG){
		*(chip+reg) = value;
	}
	switch (reg){
		case ZF:
			*(chip + CC)= value & 0x01;
			return 1;
		case  SF:
			*(chip + CC) = (value & 0x01) << 1;
			return 1;
		case OF:
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

int littleEndianInt(unsigned char* memory, int lowest, int* ret){
	return 0;
}

int bigEndianInt(unsigned char* memory, int highest, int* ret){
	return 0;
}

int instructionLength(int icode){
	return 0;
}

void printState(unsigned char* memory, int* chip){
	int* state = (int*)malloc(sizeof(int) * CHIP_SZ);
}




