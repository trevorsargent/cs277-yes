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

###functions to have: 
- int instructionLengthLookup(int icode)
- int harwareRead(int* hardware, int selector)
- void hardwareWrite(int* hardware, int selector, int value)
- immediate value reader (char * first of 8)
- reading in file(converting it from ascii to ligit hex, stored in a character)
- int memoryRead(char* address)
- void memoryWrite(char* address, int value) 




###other stuff:
- registers are an array, pass register pointer arround everywhere. 
- hardware array (integers) big array with registers, and flags, program counter, stack pointers, any other 'hardware'
- instruction array (characters) 

###File Structure 

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
