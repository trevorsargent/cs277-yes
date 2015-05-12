void halt(int * chip, int ifun);

void noop(int * chip, int ifun);

void rrmovl(unsigned char * memory, int * chip, int ifun);

void irmovl(unsigned char * memory, int * chip, int ifun);

void rmmovl(unsigned char * memory,int * chip, int ifun);

void mrmovl(unsigned char * memory, int * chip, int ifun);

void op(unsigned char * memory, int * chip, int ifun);

void jmp(unsigned char * memory, int * chip, int ifun);

void call(unsigned char * memory, int * chip, int ifun);

void ret(unsigned char * memory, int * chip, int ifun);

void push(unsigned char * memory, int * chip, int ifun); 

void pop(unsigned char * memory, int * chip, int ifun);

