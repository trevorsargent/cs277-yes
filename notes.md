#Yes

##Decisions
Take in ASCII

##Process

###preflight: 
- establish memory (array of 2^19 chars)
- read in the file
- set the program counter to 0 (or beginning of the file)
- set up stack (points)
- set up registers (more pointers)
- set up flags
- make sure we know where the end of the stack

###keep track of:
- status
- number of status


once that's all set...
##Sequential execution

###functions to have: (DONE)
- int instructionLengthLookup(int icode)
- int harwareRead(int* hardware, int selector)
- void hardwareWrite(int* hardware, int selector, int value)
- immediate value reader (char * first of 8)
- reading in file(converting it from ascii to ligit hex, stored in a character)
- int memoryRead(char* address)
- void memoryWrite(char* address, int value) 


###Hardware Array
- chip
	- 0-7 registers
		- %eax - 0
    	- %ecx - 1
    	- %edx - 2
    	- %ebx - 3
    	- %esp - 4
    	- %ebp - 5
    	- %esi - 6
    	- %edi - 7
	- 8 stack pointer
	- 9 stack frame
	- 10 PC
	- 11 flags and status (use lower 3+2 bits)
		- mask 0001 for ZF, 
		- mask 0010 for SF,
		- mask 0100 for OF, 
		- mask 11000 for Status
			- 00 for AOK, 
			- 01 for HALT, 
			- 10 for invalid address, 
			- 11 for invalid instruction)
	- 12 for bottom of stack

###other stuff:
- registers are an array, pass register pointer arround everywhere. 
- hardware array (integers) big array with registers, and flags, program counter, stack pointers, any other 'hardware'
- instruction array (characters) 

##File Structure 

- driver.c
	- main()
- tools.c
	- lengthLookup()
	- hardwareRead()
	- hardwareWrite()
	- memoryRead()
	- memoryWrite()
	- immediateValueReader()
- code1.c
	- 
