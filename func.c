#include <stdio.h>
#include <stdlib.h>

void letext(const char *argv[], int mem[]){
//lendo .text
	FILE *f;
	int lSize;

	f = fopen(argv[1],"rb");
	if(f == NULL){
		printf("Erro ao abrir o arquivo\n");
	}
//lSize = num de bytes do arquivo de entrada
	fseek (f , 0 , SEEK_END);
	lSize = ftell (f);
	rewind (f);
//copiando a entrada pra memória	
	for (int i = 0; i < lSize/4; i++){
		fread(&mem[i], 4, 1, f);
	}
	fclose(f);
}

void ledata(const char *argv[], int mem[]){
	FILE *f;
	int lSize;
	
	f = fopen(argv[2],"rb");
	if(f == NULL){
		printf("Erro ao abrir o arquivo\n");
	}
//lSize = num de bytes do arquivo de entrada
	fseek (f , 0 , SEEK_END);
	lSize = ftell (f);
	rewind (f);
//copiando a entrada pra memória	
	for (int i = 0x2000/4; i < 0x2000/4 + lSize/4; i++){
		fread(&mem[i], 4, 1, f);
	}
	fclose(f);
}

void add(int bancoReg[], int rs, int rt, int rd){
	bancoReg[rd] = bancoReg[rs] + bancoReg[rt];
}

void sub(int bancoReg[], int rs, int rt, int rd){
	bancoReg[rd] = bancoReg[rs] - bancoReg[rt];
}

void addi(int bancoReg[], int rs, int rt, int immediate){
	bancoReg[rt] = bancoReg[rs] + immediate;
}

void addiu(int bancoReg[], int rs, int rt, int immediate){
	bancoReg[rt] = bancoReg[rs] + (unsigned)immediate;
}
/*
void mult(int bancoReg[], int rs, int rt,int *HI, int *LO){
	long long int aux,mascHI,mascLO;

	aux = bancoReg[rs] * bancoReg[rt];
	mascHI = 0xffffffff00000000;
	mascLO = 0x00000000ffffffff;

	*HI = (int)((aux & mascHI) >> 32);
	*LO = (int)(aux & mascLO);
}
*/
void divv(int bancoReg[], int rs, int rt,int *HI, int *LO){
	*HI = bancoReg[rs]%bancoReg[rt];
	*LO = bancoReg[rs]/bancoReg[rt];
}

void mfhi(int bancoReg[], int rd, int *HI){
	bancoReg[rd] = *HI;
}

void mflo(int bancoReg[], int rd, int *LO){
	bancoReg[rd] = *LO;
}

void and(int bancoReg[], int rs, int rt, int rd){
	bancoReg[rd] = bancoReg[rs] & bancoReg[rt];
}

void or(int bancoReg[], int rs, int rt, int rd){
	bancoReg[rd] = bancoReg[rs] | bancoReg[rt];
}

void slt(int bancoReg[], int rs, int rt, int rd){
	bancoReg[rd] = (bancoReg[rs] < bancoReg[rt]);
}

void sll(int bancoReg[], int rt, int rd, int shamt){
	bancoReg[rd] = bancoReg[rt] << shamt;
}

void srl(int bancoReg[], int rt, int rd, int shamt){
	bancoReg[rd] = bancoReg[rt] >> shamt;
}

void jr(int bancoReg[], int rs, int *PC){
	*PC = bancoReg[rs];
}

void j(int mem[], int *PC, int immediate){
	int masc = 0xf0000000,pc,C;

	pc = (mem[(*PC)+1] & masc);//pc = $PC[31-28];
	C  = immediate << 2;
	*PC = (pc | C);
}

void jal(int mem[], int bancoReg[], int immediate, int *PC){
	bancoReg[31] = mem[*PC];
	j(mem,PC,immediate);
}

void syscall(int bancoReg[],int *EXIT){
	char *string;
	int n;
 	int r;
	switch(bancoReg[2])
	{
		case 1:
			printf("%d", bancoReg[4]);
		break;

		/*case 2:
			printf("%s\n", );
		break;

		case 3:

		break;*/

		case 4:
			printf("%s", (char *)bancoReg[4]);
		break;

		case 5:
			scanf("%d",&bancoReg[2]);
		break;

		/*case 6:
			scanf("%f");
		break;

		case 7:
			scanf("%lf");
		break;*/

		case 8:
			string = (char *) malloc((bancoReg[5]+1)*sizeof(char));

			scanf("%s", string);
			bancoReg[4] = (int)string;
			free(string);
		break;

		case 10:
			*EXIT = 1;
		break;

		case 11:
			printf("%c", bancoReg[4]);
		break;

		case 12:
			scanf("%c",&bancoReg[2]);
		break;

		case 34:
			printf("%08x", bancoReg[4]);
		break;

		case 35:
			n = bancoReg[4];  
			for(int i = 31; i >= 0; i--) {
    			r = n >> i;
			    if(r & 1) 
        			printf("1");
    			else 
	        		printf("0");
 			}
		break;

		case 36:
			printf("%u", bancoReg[4]);
		break;
	}
}

void tipoR(int bancoReg[], int rs, int rt, int rd, int shamt, int funct, int *HI, int *LO, int *PC){
	switch(funct){
		//add
		case 0x20:
			add(bancoReg, rs, rt, rd);
		break;
	
		//sub
		case 0x22:
			sub(bancoReg, rs, rt, rd);
		break;
		
		//mult
		case 0x18:
		//mult(bancoReg, rs, rt, rd);
		break;

		//divv
		case 0x1a:
			divv(bancoReg, rs, rt, HI, LO);
		break;

		//mfhi
		case 0x10:
			mfhi(bancoReg, rd, HI);
		break;

		//mflo
		case 0x12:
			mflo(bancoReg, rd, LO);
		break;

		//and
		case 0x24:
			and(bancoReg, rs, rt, rd);
		break;

		//or
		case 0x25:
			or(bancoReg, rs, rt, rd);
		break;

		//slt
		case 0x2a:
			slt(bancoReg, rs, rt, rd);
		break;

		//sll
		case 0x0:
			sll(bancoReg,rt,rd,shamt);
		break;

		//srl
		case 0x2:
			srl(bancoReg,rt,rd,shamt);
		break;

		//jr
		case 0x8:
			jr(bancoReg,rs,PC);
		break;
	}
}

void tipoI(int bancoReg[], int opcode,int rs, int rt, int immediate){
	switch(opcode){
		case 0x8:
			bancoReg[rt] = bancoReg[rs] + immediate;
		break;
	}
}
/*	
	jump opcode == 000010;
	jal  opcode == 000011;
*/
void tipoJ(int mem[], int bancoReg[], int opcode, int immediate, int *PC){
	switch(opcode){
		//jump
		case 0x2:
			j(mem,PC,immediate);
		break;

		//jal
		case 0x3:
			jal(mem,bancoReg, immediate, PC);
		break;
	}
}