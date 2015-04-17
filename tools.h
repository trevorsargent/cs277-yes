#include <stdio.h>
#include <stdlib.h>

/*
	converts an ascii pair to a 1 byte hex value
*/
unsigned char hexConvert(char, char);
// hexConvert(a, b) -> 0xAB

/*
	read file into the lower order values of the main memory, 
	returns the first address that's free above the program code.
*/
int readFile(int, char*[], unsigned char*);
// readFile(argc, *argv[], memory)

/*
	read from memory
	takes memory address, and returns the value stored in that byte
	exits program if illegal memory is accessed
*/
unsigned char memRead(int*, int);
// memRead(memory, 0x0007FFFF) -> value at 0x000FFFFF

/*
	write memory
	writes, to memory address provided, the value provided. 
	exits program if illgal memory is accessed
*/
void memWrite(int*, int, int);
// memWrite(memory, 0x0007FFFF, 0x12345678) -> writes 0x000844DD to 0x0007FFFF

/*
	read from chip
	reads, from the chip, the contents of the register designated by the flag passed
*/
int chipRead(int*, int);
// chipRead(chip, 0) -> value at %eax (register 0)

/*
	write to chip
	writes, to the chip, the value provided at the register designated by the flag passed
*/
void memRead(int*, int, int);
// memRead(chip, 0, 0x55667788) -> writes 0x55667788 to %eax (register 0)

/*
	immediate value translator - good for program code
	takes the *lowest* address of 4 bytes of hex stored, and returns a *little endian* interpreation of that number. 
	example: 
	0x105: FF
	0x106: 33
	0x107: DD
	0x108: 99
	littleEndianInt(int* memory, 0x105); would return 0x99DD33FF
*/
int littleEndianInt(int* , int);

/*
	immediate value translator - good for the stack
	takes the *hightest* address of 4 bytes of hex, and returns a *big endian* interpreation of that number. 
	example: 
	0x105: FF
	0x106: 33
	0x107: DD
	0x108: 99
	bigEndianInt(int* memory, 0x108); would return 0x99DD33FF
*/
int bigEndianInt(int*, int);

/*
	instruction length lookup
	takes the icode and returns the instruction length in bytes
*/
int instructionLength(int);
