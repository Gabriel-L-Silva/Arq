#include <stdio.h>
#include <stdlib.h>
#include "func.h"

typedef char String[32];
int main(int argc, const char *argv[]){	
	int mem[1024*4] = {0};
	int bancoReg[32] = {0};
	int PC = 0;
	int mascara;
	int inst;
	int opcode;
	int rs,rt,rd,shamt,funct;
	int immediate;
	int EXIT = 0;
	int HI = 0,LO = 0;
//	int bancoReg[32] = {0};

//Confere se o numero de argumentos está correto
	if(argc != 3){
		printf("Numero de argumentos invalidos\n");
		return 1;
	}

//	Começo Leitura
//Le arquivo text.bin e salva na memória	
	letext(argv,mem);
//Le arquivo data.bin e salva na memória
	ledata(argv,mem);
//	Fim Leitura
//	Inicio Decode
	while(EXIT == 0){
		inst = mem[PC];
		printf("	%d 		%08x\n", PC,inst);
		mascara = 0xfc000000;
		opcode  = (inst & mascara) >> 26;
		if(inst == 0xc){
			syscall(bancoReg,&EXIT);
		}else if(opcode == 0){
			mascara = 0x3e00000;
			rs = (inst & mascara) >> 21;
			rt = (inst & (mascara >> 5)) >> 16;
			rd = (inst & (mascara >> 10)) >> 11;
			shamt = (inst & (mascara >> 15)) >> 6;
			mascara = 0x3f;
			funct = (inst & mascara);
			tipoR(bancoReg, rs, rt, rd, shamt, funct,&HI,&LO,&PC);
		}
		else if(opcode != 0x10 && opcode != 0x11){
			mascara = 0x3e00000;
			rs = (inst & mascara) >> 21;
			rt = (inst & (mascara >> 5)) >> 16;
			mascara = 0x0000ffff;
			immediate = (inst & mascara);
			tipoI(bancoReg, opcode, rs, rt, immediate);
		}else{
			immediate = inst >> 6;
			tipoJ(mem,bancoReg, opcode, immediate, &PC);
		}
		PC++;
	}
	for (int i = 0; i < 32; ++i)
	{
		printf("%08x\n", bancoReg[i]);
	}
	return 0;
}