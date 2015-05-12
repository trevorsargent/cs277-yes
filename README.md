#Yes
##CS 277 Final Project

A Y86 virtual machine/Sequential Simulator by Dom Mills & Trevor Sargent, under the instruction of Michael Harmon as part of CS277, Architecture and Assembly course at Lewis & Clark College. 


##To Run:
```
$ make clean; make
$ ./yes example\ binaries/call.yo
```
or supply a path to any other object file that follows the reduced instruction set described herein. 

##Instruction Set / Visible State

###Registers

####8 General Purpose Regiesters with Numerical Encodings
- %eax: 0
- %ecx: 1
- %edx: 2
- %ebx: 3
- %esp: 4
- %ebp: 5
- %esi: 6
- %edi: 7

#### Condition Code Registers
- ZF
- SF 
- OF 

#### Program Counter Register
- PC

#### Status Register
- STAT 
	- AOK
	- HALT
	- INVAD (invalid address)
	- INVIN (invalid instruction)


###Memory
For this assignment, the addressable space is requred to be from 0 - 2 <sup>32</sup> -1

###Instructions
Y86 uses a variable length instruction encoding, they vary from 1-6 bytes 

- byte 0: instruction|function endcoding
- byte 1: 1 byte registers   
- bytes 2 - 4: 4 bytes of immediate value / offset 

NOTE: LITTLE ENDIAN BYTE ORDERING

Instruction | Byte 0 | 1 | 2 | 3 | 4 | 5 | notes   
--- | --- | --- | --- | --- | --- | --- | ---  
`halt`|0x00| | | | | | 
`nop`|0x10| | | | | | 
`rrmovl rA,rB`|0x20|rArB| | | | | (%eax to %ecx would be 0x01)   
`irmovl v, rB`|ox30|FrB|1F|01|00|00|(register A is immediate (F) and bytes are listed from most to lease significant)
`rmmovl RA, D(vB)`|0x40|rArB|00|00|00|00|offset value D is in the value bytes
`mrmovl D(rA), rB`|0x50|rArB|00|00|00|00|ditto
`jmp`|0x70|00|00|00|00| |location goes in value
`jxx`|0x7x|00|00|00|00| |location goes in value, variation in j[xx] dictates respective variation in 7[x] 
`OP rA, rB`|0x6X|rArB| | | | | 
`cmovXX: rA, rB`|0x2X|rArB| | | | | 
`call NAME`|0x80| | | | | | 
`ret`|0x90| | | | | | 
`push rA`|0xA0|rArF| | | | | 
`pop rA`|0xB0|rArF| | | | | 

#### ALU Operations
0x6x

- addl: 0
- subl: 1 (cmp)
- andl: 2 (test)
- xorl: 3

Condition flags are set identically to IA-32   

#### Conditional Jumps / Moves
`j+below` or `cmovl+below`

- le: 1 (<=)
- l: 2 (<)
- e: 3 (==)
- ne: 4 (!=)
- ge: 5 (>=)
- g: 6 (>)

Instructions for the conditional moves follow the same conventions. 
