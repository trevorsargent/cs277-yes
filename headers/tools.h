// #include <stdio.h>
// #include <stdlib.h>

/*
	converts an ascii pair to a 1 byte hex value
*/
unsigned char hexConvert(char, char);
// hexConvert(a, b) -> 0xAB

/*
	read file into the lower order values of the main memory, 
	returns the first address that's free above the program code.
	
	readFile(argc, *argv[], memory) -> success (1/0)
*/
int readFile(int argc, char** argv, unsigned char* memory);


/*
	read from memory
	reads, and returns, byte value at 'address'

	memRead(memory, 0x0007FFFF) -> byte value at 0x0007FFFF
*/
int memRead(unsigned char* memory, int* chip, int address);


/*
	write to memory
	writes the integer value provided to 4 contiguous bytes starting with the address provided, moving up.  
	set system status

	memWrite(memory, 0x0007FFFF, 0x12345678) -> writes 0x000844DD to 0x0007FFFF
*/
int memWrite(unsigned char* memory, int* chip, int address, int value);


/*
	read from chip
	reads, from the chip, the contents of the register designated by the flag passed
	returns value read from chip. 
	set status

	chipRead(chip, EAX) -> reades, and returns, the integer value in %eax. 
*/
int chipRead(int* chip, int reg);


/*
*	write to chip
	writes, to the chip, the value provided at the register designated by the flag passed
	returns, 0 if failed, 1 if success. 
	set status

	chipWrite(chip, EAX, 0x55667788) -> writes 0x55667788 into %eax 
*/
int chipWrite(int* chip, int reg, int value);

/*
	immediate value translator - good for program code, executable instruction value bytes.
	takes the *lowest* address of 4 bytes of hex stored, and returns a *little endian* interpreation of that number. 
	
	example: 
	0x108: 99
	0x107: DD
	0x106: 33
	0x105: FF

	littleEndianInt(int* memory, 0x105); would return 0x99DD33FF

	set status

	littleEndianInt(memory, chip, 0x105) -> 
*/
int littleEndianInt(unsigned char* memory, int* chip, int lowest);

/*
	instruction length lookup
	takes the icode and returns the instruction length in bytes
	returns 0 if invalid instruction
*/
int instructionLength(int icode);

/*
	returns a lookup of the instruction length to increment the program counter
*/
void printState(int* chip);

/*
	initializes registers
*/
void chipSetup(int* chip);

/*
	increments program counter by ammount passed
*/
void pincrement(int * chip, int length);

