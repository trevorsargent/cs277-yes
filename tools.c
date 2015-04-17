#include "tools.h"

//returns the 8 bits of the binary representation of the 2 digit hex value passed: 'A','B' -> 0xAB 
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
		fgetc(fp);
		*(memory + i) = hexConvert(a, b);
		i++;
	}while(!feof(fp) && !ferror(fp));
	
	return i;
}




