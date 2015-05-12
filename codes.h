//Genearal Purpose Registers

#define EAX 0 // Return Register
#define ECX 1
#define EDX 2
#define EBX 3
#define ESP 4 // Stack Pointer
#define EBP 5 // Stack Frame Pointer
#define ESI 6
#define EDI 7

// Special Purpose Registers

// Program Counter 
#define PC 8

// Top of the program code
#define SEG 9

// Number of instructions executed
#define NUMOPS 10

// Condition Flags
#define CC 11

#define CZ 12
#define CS 13
#define CO 14

// System Status, and possible states
#define STAT 15


#define AOK 16
#define HALT 17
#define INVAD 18 // Invalid Address
#define INVIN 19 // Invalid Instruction

// Constants

#define MAXMEM 0x7FFFF // Highest availble memory address
#define MEM_SZ 0x80000 // Memory Size

#define CHIP_SZ 12 // Number of 'registers' on the 'chip'
