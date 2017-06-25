#include <stdio.h>
#include <stdlib.h>
#include "func.h"
/*	
	jump opcode == 000010;
'	jal  opcode == 000011;
*/
typedef char String[32];
int main(int argc, const char *argv[]){	
	unsigned int mem[1024*4] = {0};
	unsigned int *PC = mem;
	unsigned int mascara;
	unsigned int inst;
	unsigned int opcode;
	char rs,rt,rd,shamt,funct;
	int immediate;
	char tipo;
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
	while(*PC != 0){
		inst = *PC;
		mascara = 0xfc000000;
		opcode  = (inst & mascara) >> 26;
		if(opcode == 0){
			mascara = 0x3e00000;
			rs = (inst & mascara) >> 21;
			rt = (inst & (mascara >> 5)) >> 16;
			rd = (inst & (mascara >> 10)) >> 11;
			shamt = (inst & (mascara >> 15)) >> 6;
			mascara = 0x3f;
			funct = (inst & mascara);
			printf("Tipo R:\n");
			printf("%08x	%08x	%08x	%08x	%08x\n", rs,rt,rd,shamt,funct);
		}
		else if(opcode != 0x10 && opcode != 0x11){
			mascara = 0x3e00000;
			rs = (inst & mascara) >> 21;
			rt = (inst & (mascara >> 5)) >> 16;
			mascara = 0x0000ffff;
			immediate = (inst & mascara);
			printf("Tipo I:\n");
			printf("%08x	%08x	%08x\n", rs,rt,immediate);
		}else{
			immediate = inst >> 6;
		}
		PC++;
	}
	return 0;
}