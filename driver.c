#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

int main(int argc, char *argv[]){
	//hardware
	int* hardware = malloc(sizeof(int) * )



	if(argc > 2){
		puts("Error: More than 1 executable supplied.");
	} else if(argc < 2){
		puts("Welcome to YES, a y86 virtual machine. please supply a .yo executable on the command line.");
	}else{
		FILE *fp = fopen(argv[1], "r");
		if(fp == 0){
			printf("Error: Could not open file <%s>\n",argv[1]);
		}else{
			puts("Status: Reading file");
		}
		//do the things
	}
	return 0;
}