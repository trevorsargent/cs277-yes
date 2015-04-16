#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include <math.h>

int main(int argc, char *argv[]){
	//hardware
		//0-7 registers
			//%eax - 0
	    	//%ecx - 1
	    	//%edx - 2
	    	//%ebx - 3
	    	//%esp - 4
	    	//%ebp - 5
	    	//%esi - 6
	    	//%edi - 7
		//8 stack pointer
		//9 stack frame
		//10 PC
		//11 flags and status (use lower 3+2 bits)
			//mask #0001 for ZF, 
			//mask #0010 for SF,
			//mask #0100 for OF, 
			//mask #11000 for Status
				//#00 for AOK, 
				//#01 for HALT, 
				//#10 for invalid address, 
				//#11 for invalid instruction)
	int* hardware = malloc(sizeof(int) * 11);
	unsigned char* memory = malloc(sizeof(char) * pow(2,19));

	
	//set up file. 
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
	

	int stackBottom = readFile(fp, memory);
	int i;
	
	for(i = 0; i<stackBottom; i++){
		printf("%x ", *(memory+i));
	}
	printf("\n");
	
	return 0;
}