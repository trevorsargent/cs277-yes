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
*/
int readFile(int argc, char** argv, unsigned char* memory);
// readFile(argc, *argv[], memory)

/*
	read from memory
	reads value at memory adddress into the variable passed. 
	returns 1 if successful and legal, otherwise 0
*/
int memRead(unsigned char* memory, int* chip, int address);
// memRead(memory, 0x0007FFFF) -> value at 0x000FFFFF

/*
	write memory
	writes, to memory address provided, the value provided. 
	returns 1 if successful and legal, otherwise 0
	set system status
*/
int memWrite(unsigned char* memory, int* chip, int address, unsigned char value);
// memWrite(memory, 0x0007FFFF, 0x12345678) -> writes 0x000844DD to 0x0007FFFF

/*
	read from chip
	reads, from the chip, the contents of the register designated by the flag passed
	returns value read from chip. 
	set status

*/
int chipRead(int* chip, int reg);
// chipRead(chip, EAX) -> reades, and returns, value at %eax. 

/*
*	write to chip
	writes, to the chip, the value provided at the register designated by the flag passed
	returns, 0 if failed, 1 if success. 
	set status

*/
int chipWrite(int* chip, int reg, int value);
// chipWrite(chip, EAX, 0x55667788) -> writes 0x55667788 to %eax 

/*
	immediate value translator - good for program code, executable instruction value bytes.
	takes the *lowest* address of 4 bytes of hex stored, and returns a *little endian* interpreation of that number. 
	example: 
	0x105: FF
	0x106: 33
	0x107: DD
	0x108: 99
	littleEndianInt(int* memory, 0x105); would return 0x99DD33FF
	set status
*/
int littleEndianInt(unsigned char* memory, int lowest);

/*
	immediate value translator - good for the stack
	takes the *hightest* address of 4 bytes of hex, and returns a *big endian* interpreation of that number. 
	example:
	0x108: 99 
	0x107: DD
	0x106: 33
	0x105: FF
	bigEndianInt(int* memory, 0x108); would return 0xFF33DD99
*/
int bigEndianInt(unsigned char* memory, int highest);

/*
	instruction length lookup
	takes the icode and returns the instruction length in bytes
	returns 0 if invalid instruction
*/
int instructionLength(int icode);

void printState(int* chip);
void chipSetup(int* chip);
