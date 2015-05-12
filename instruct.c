#include "codes.h"
#include "tools.h"
#include "instruct.h"
#include <stdio.h>

void halt(int * chip, int ifun){
	//puts("halt!");
	if(ifun != 0){
		chipWrite(chip, STAT, INVIN);
		return;
	}
	chipWrite(chip, STAT, HALT);
	return;
}

void noop(int *chip, int ifun){
	//puts("noop");
	if(ifun!=0){
		chipWrite(chip, STAT, INVIN);
		return;
	}
	
}

void rrmovl(unsigned char * memory, int * chip, int ifun){
	//puts("(c)rrmovl");
	unsigned char rA, rB;
	rA = (memRead(memory, chip, chipRead(chip, PC)+1)>>4) & 0xF;
	rB = memRead(memory, chip, chipRead(chip, PC )+1) & 0x0F;
	if(rA >= 8 || rB >= 8){
		chipWrite(chip, STAT, HALT);
		return;
	}
	unsigned char zf = chipRead(chip, CZ);
	unsigned char sf = chipRead(chip, CS);
	unsigned char of = chipRead(chip, CO);
	switch(ifun){
		case 0x0:
			chipWrite(chip, rB, chipRead(chip, rA));
			break;
		case 0x1:
			if((sf ^ of)|zf){
				chipWrite(chip, rB, chipRead(chip, rA));
			}
			break;
		case 0x2:
			if(sf ^ of){
				chipWrite(chip, rB, chipRead(chip, rA));
			}
			break;
		case 0x3: 
			if(zf){
				chipWrite(chip, rB, chipRead(chip, rA));
			}
			break;
		case 0x4:
			if(!zf){chipWrite(chip, rB, chipRead(chip, rA));}
			break;
		case 0x5:
			if(!(sf^zf)){chipWrite(chip, rB, chipRead(chip, rA));}
			break;
		case 0x6:
			if(!(sf^zf)&(~zf)){chipWrite(chip, rB, chipRead(chip, rA));}
			break;
		default:
			chipWrite(chip, STAT, HALT);
			break;
	}
	return;
}

void irmovl(unsigned char * memory, int * chip, int ifun){
	unsigned char rA, rB;
	rA = (memRead(memory, chip, chipRead(chip, PC)+1)>>4);
	rB = memRead(memory, chip, chipRead(chip, PC)+1) & 0x0F;


	if((ifun != 0) || (rA != 0x0F)){
		chipWrite(chip, STAT, INVIN);
		return;
	}

	int value = littleEndianInt(memory, chip, chipRead(chip, PC)+2);
	
	chipWrite(chip, rB, value);

	//puts("irmovl");
	return;
	
	
}

void rmmovl(unsigned char * memory, int * chip, int ifun){
	//puts("rmmovl");
	unsigned char rA, rB;
	rA = (memRead(memory, chip, chipRead(chip, PC )+1)>>4) & 0x0F;
	rB = memRead(memory, chip, chipRead(chip, PC )+1) & 0x0F;
	
	if((ifun != 0) || (rA != 0x0F)){
		chipWrite(chip, STAT, INVIN);
		return;
	}

	int offset = littleEndianInt(memory, chip, chipRead(chip, PC)+4);
	int location = rB + offset;
	unsigned char byte;

	byte = (unsigned char)(chipRead(chip, rA));
	memWrite(memory, chip, location, byte);
	byte = (unsigned char)((chipRead(chip, rA)>>8));
	memWrite(memory, chip, location+1, byte);
	byte = (unsigned char)((chipRead(chip, rA)>>16));
	memWrite(memory, chip, location+2, byte);
	byte = (unsigned char)((chipRead(chip, rA)>>24));
	memWrite(memory, chip, location+3, byte);

	return;
}

	

void mrmovl(unsigned char * memory, int * chip, int ifun){
	//puts("mrmovl");
	unsigned char rA, rB;
	rA = (memRead(memory, chip, chipRead(chip, PC )+1)>>4) & 0x0F;
	rB = memRead(memory, chip, chipRead(chip, PC )+1) & 0x0F;
	
	if((ifun != 0) || (rA != 0x0F)){
		chipWrite(chip, STAT, INVIN);
		return;
	}

	int offset = littleEndianInt(memory, chip, chipRead(chip, PC)+4);
	int value = littleEndianInt(memory, chip, chipRead(chip, rA)+offset);
	chipWrite(chip, rB, value);

	return;

}

void op(unsigned char * memory, int * chip, int ifun){
	//puts("op!");
	unsigned char rA, rB;
	rA = (memRead(memory, chip, chipRead(chip, PC )+1)>>4) & 0x0F;
	rB = memRead(memory, chip, chipRead(chip, PC )+1) & 0x0F;
	int a = chipRead(chip, rA);
	int b = chipRead(chip, rB);
	int t;
	
	switch(ifun){
		case 0:
			chipWrite(chip, rB, a + b);
			t=a+b;
			break;
				
		case 1: 
			chipWrite(chip, rB, b - a);
			t=b-a;
			break;
		case 2:  
			chipWrite(chip, rB, a & b);
			t=a&b;
			break;
		case 3: 
			chipWrite(chip, rB, a ^ b);
			t=a^b;
			break;
		default:
			chipWrite(chip, STAT, INVIN);
	}

	chipWrite(chip, CZ, t==0);
	chipWrite(chip, CS, t<0);
	chipWrite(chip, CO, (a<0 == b<0) && (t < 0 != a < 0));	

	return;		

}

void jmp(unsigned char * memory, int * chip,  int ifun){
	//puts("jmp!");
	unsigned char zf = chipRead(chip, CZ);
	unsigned char sf = chipRead(chip, CS);
	unsigned char of = chipRead(chip, CO);
	int dest = littleEndianInt(memory, chip, chipRead(chip, PC)+1);
	int flag = 0;
	switch(ifun){
		case 0x0:
			flag = 1;
			break;
		case 0x1:
			if((sf ^ of)|zf){
				flag = 1;
			}
			break;
		case 0x2:
			if(sf ^ of){
				flag = 1;
			}
			break;
		case 0x3: 
			if(zf){
				flag = 1;
			}
			break;
		case 0x4:
			if(!zf){
				flag = 1;
			}
			break;
		case 0x5:
			if(!(sf^zf)){
				flag = 1;
			}
			break;
		case 0x6:
			if(!(sf^zf)&(~zf)){
				flag = 1;
			}
			break;
		default:
			chipWrite(chip, STAT, INVIN);
			break;
		
	}
	if(flag){
		chipWrite(chip, PC, dest-5);
	}
	return;

}

void call(unsigned char * memory, int * chip, int ifun){
	//puts("call");

	/*
	decrement esp
	*(esp) = &nextInstruction (PC + 5)
	decrement esp
	*(esp) = ebp
	ebp = esp
	

	*/

	
	
	//decrement stack pointer (by 4) 'pushing'
	chipWrite(chip, ESP, chipRead(chip, ESP)-4);
	
	//write return address (pc+5) (address of next instruction)
	memWrite(memory, chip, chipRead(chip, ESP), chipRead(chip, PC)+5); //*(esp) = &nextInstruction
	//decrement stack pointer (by 4) 'pushing'
	chipWrite(chip, ESP, chipRead(chip, ESP)-4);
	//write value of ebp 
	memWrite(memory, chip, chipRead(chip, ESP), chipRead(chip, EBP));
	//set the value at ebp to value of stack pointer
	chipWrite(chip, EBP, chipRead(chip, ESP));
	
	//program counter set to value in the instruction
	chipWrite(chip, PC, littleEndianInt(memory, chip, chipRead(chip, PC)+1)-5);
	//printf("im updating pc to 0x%08x in the call function", chipRead(chip, PC));
	return;
}

void ret(unsigned char * memory, int * chip, int ifun){
	//puts("ret");

	/*
	esp = ebp
	ebp = *(ebp)
	esp += 4
	pc = *(esp)
	esp += 4
	
	*/

	//esp = ebp NOT esp = *(ebp) make esp point to where ebp is pointing
	chipWrite(chip, ESP, chipRead(chip, EBP));
	//set ebp back to value stored at memory location stored in ebp - ebp = *(ebp)
	chipWrite(chip, EBP, littleEndianInt(memory, chip, chipRead(chip, EBP)));
	//increment esp - 
	chipWrite(chip, ESP, chipRead(chip, ESP)+4); //now it's pointing at the memory address that holds the address of the next instruction
	//set program counter to value at esp
	chipWrite(chip, PC, littleEndianInt(memory, chip, chipRead(chip, ESP))-1);
	//printf("im updating pc to 0x%08x in the ret function", chipRead(chip, PC));
	//increment esp
	chipWrite(chip, ESP, chipRead(chip, ESP)+4);
	return;

}

void push(unsigned char * memory, int * chip, int ifun){
	//puts("push");
	unsigned char rA, rB;
	rA = (memRead(memory, chip, chipRead(chip, PC)+1)>>4) & 0x0F;
	rB = memRead(memory, chip, chipRead(chip, PC)+1) & 0x0F;
	if(rB!=0xF || ifun != 0){
		chipWrite(chip, STAT, INVIN);
		return;
	}

	chipWrite(chip, ESP, chipRead(chip, ESP) -4);
	memWrite(memory, chip, chipRead(chip, ESP), chipRead(chip, rA));
	//printf("*(ESP): 0x%08x\n", littleEndianInt(memory, chip, chipRead(chip, ESP)));
	return;
}

void pop(unsigned char * memory, int * chip, int ifun){
//puts("pop");
	unsigned char rA, rB;
	rA = (memRead(memory, chip, chipRead(chip, PC)+1)>>4) & 0x0F;
	rB = memRead(memory, chip, chipRead(chip, PC)+1) & 0x0F;
	if(rB!=0xF || ifun != 0){
		chipWrite(chip, STAT, INVIN);
		return;
	}
	chipWrite(chip, rA, littleEndianInt(memory, chip, chipRead(chip, ESP)));
	chipWrite(chip, ESP, chipRead(chip, ESP) +4);
	return;
}
