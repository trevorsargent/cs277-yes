#include "tools.h"

//returns the 8 bits of the binary representation of the 2 digit hex value passed: 'A','B' -> 0xAB 
unsigned char hexConvert(char a, char b){
	int i =0;
	unsigned ret = 0x00;
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