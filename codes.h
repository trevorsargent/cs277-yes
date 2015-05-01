#define EAX 0
#define ECX 1
#define EDX 2
#define EBX 3
#define ESP 4
#define EBP 5
#define ESI 6
#define EDI 7
#define PC 8
#define SEG 9
#define CC 10 //do not access this directly, always reference by the registers listed below
#define NUMOPS 11


#define CZ 11
#define CS 12
#define CO 13
#define STAT 14

#define AOK 15
#define HALT 16
#define INVAD 17
#define INVIN 18

#define TRUE 1
#define FALSE 0
#define INVALID 

#define MAXMEM 0x7FFFF
#define MEM_SZ 0x80000

#define CHIP_SZ 12