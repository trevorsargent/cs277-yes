#include "codes.h"
#include "tools.h"
#include "instruct.h"
#include <stdio.h>


// 'halt' 
void halt(int * chip, int ifun){
	if(ifun != 0){
		chipWrite(chip, STAT, INVIN);
		return;
	}
	chipWrite(chip, STAT, HALT);
	return;
}

void noop(int *chip, int ifun){
	if(ifun!=0){
		chipWrite(chip, STAT, INVIN);
		return;
	}
	
}

void rrmovl(unsigned char * memory, int * chip, int ifun){
	unsigned char rA, rB;

	// extract the registers from the second byte of the instruction
	rA = (memRead(memory, chip, chipRead(chip, PC)+1)>>4) & 0xF;
	rB = memRead(memory, chip, chipRead(chip, PC )+1) & 0x0F;

	// make sure instruction is valid
	if(rA >= 8 || rB >= 8){
		chipWrite(chip, STAT, INVIN);
		return;
	}

	// declare 'shortcut' variables for the condition codes
	unsigned char zf = chipRead(chip, CZ);
	unsigned char sf = chipRead(chip, CS);
	unsigned char of = chipRead(chip, CO);


	// branch based on instruction
	// set condition

	int move = 0;
	switch(ifun){
		case 0x0: 
			move = 1; 
			break;
		case 0x1:
			if((sf ^ of)|zf){
				move = 1; 
			} 
			break;
		case 0x2:
			if(sf ^ of){
				move = 1; 
			} 
			break;
		case 0x3: 
			if(zf){
				move = 1; 
			} 
			break;
		case 0x4:
			if(!zf){
				move = 1; 
			} 
			break;
		case 0x5:
			if(!(sf^zf)){
				move = 1; 
			} 
			break;
		case 0x6:
			if(!(sf^zf)&(~zf)){
				move = 1; 
			} 
			break;
		default:
			chipWrite(chip, STAT, HALT);
			break;
	}

	// if codes were appropriately set for the instruction, 
	// then execute the move from and to the registers provided
	if(move){
		chipWrite(chip, rB, chipRead(chip, rA));
	}
	return;
}

void irmovl(unsigned char * memory, int * chip, int ifun){
	unsigned char rA, rB;

	// extract the registers from the second byte of the instruction
	rA = (memRead(memory, chip, chipRead(chip, PC)+1)>>4) & 0x0F;
	rB = memRead(memory, chip, chipRead(chip, PC)+1) & 0x0F;

	if((ifun != 0) || (rA != 0x0F)){
		chipWrite(chip, STAT, INVIN);
		return;
	}

	int value = littleEndianInt(memory, chip, chipRead(chip, PC)+2);
	
	chipWrite(chip, rB, value);
	return;
	
	
}

void rmmovl(unsigned char * memory, int * chip, int ifun){

	unsigned char rA, rB;

	// extract the registers from the second byte of the instruction
	rA = (memRead(memory, chip, chipRead(chip, PC )+1)>>4) & 0x0F;
	rB = memRead(memory, chip, chipRead(chip, PC )+1) & 0x0F;
	
	// reject invalid instructions
	if((ifun != 0) || (rA != 0x0F)){
		chipWrite(chip, STAT, INVIN);
		return;
	}

	// read offset from instruction
	int offset = littleEndianInt(memory, chip, chipRead(chip, PC)+2);

	memWrite(memory, chip, rB + offset, chipRead(chip, rA));

	return;
}

	

void mrmovl(unsigned char * memory, int * chip, int ifun){
	unsigned char rA, rB;

	// extract the registers from the second byte of the instruction
	rA = (memRead(memory, chip, chipRead(chip, PC )+1)>>4) & 0x0F;
	rB = memRead(memory, chip, chipRead(chip, PC )+1) & 0x0F;
	
	// reject invalid instructions
	if((ifun != 0) || (rA != 0x0F)){
		chipWrite(chip, STAT, INVIN);
		return;
	}

	int offset = littleEndianInt(memory, chip, chipRead(chip, PC)+2);
	int value = littleEndianInt(memory, chip, chipRead(chip, rA)+offset);
	chipWrite(chip, rB, value);

	return;

}

void op(unsigned char * memory, int * chip, int ifun){
	unsigned char rA, rB;

	// extract the registers from the second byte of the instruction
	rA = (memRead(memory, chip, chipRead(chip, PC )+1)>>4) & 0x0F;
	rB = memRead(memory, chip, chipRead(chip, PC )+1) & 0x0F;

	// declare 'shortcut' variables for following switch
	int a = chipRead(chip, rA);
	int b = chipRead(chip, rB);
	int t;
	
	// branch based on instruction
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

	// set condition codes 
	chipWrite(chip, CZ, t==0);
	chipWrite(chip, CS, t<0);
	chipWrite(chip, CO, (a<0 == b<0) && (t < 0 != a < 0));	

	return;		

}

void jmp(unsigned char * memory, int * chip,  int ifun){

	// declare shortcute varables for switch
	unsigned char zf = chipRead(chip, CZ);
	unsigned char sf = chipRead(chip, CS);
	unsigned char of = chipRead(chip, CO);

	// 
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
		chipWrite(chip, PC, dest-5); // compensate for the increment that will happen outside the instruction
	}
	return;

}

void call(unsigned char * memory, int * chip, int ifun){
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

	unsigned char rA, rB;

	// extract the registers from the second byte of the instruction
	rA = (memRead(memory, chip, chipRead(chip, PC)+1)>>4) & 0x0F;
	rB = memRead(memory, chip, chipRead(chip, PC)+1) & 0x0F;

	// reject invalid instructions
	if(rB!=0xF || ifun != 0){
		chipWrite(chip, STAT, INVIN);
		return;
	}

	chipWrite(chip, ESP, chipRead(chip, ESP) -4);
	memWrite(memory, chip, chipRead(chip, ESP), chipRead(chip, rA));
	return;
}

void pop(unsigned char * memory, int * chip, int ifun){
	unsigned char rA, rB;

	// extract the registers from the second byte of the instruction
	rA = (memRead(memory, chip, chipRead(chip, PC)+1)>>4) & 0x0F;
	rB = memRead(memory, chip, chipRead(chip, PC)+1) & 0x0F;

	// reject invalid instructions
	if(rB!=0xF || ifun != 0){
		chipWrite(chip, STAT, INVIN);
		return;
	}
	chipWrite(chip, rA, littleEndianInt(memory, chip, chipRead(chip, ESP)));
	chipWrite(chip, ESP, chipRead(chip, ESP) +4);
	return;
}
