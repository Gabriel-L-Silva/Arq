#include <stdio.h>
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
void add(int *d, int s, int t){
	*d = s + t;
}
void sub(int *d, int s, int t){
	*d = s - t;
}
void addi(int *d, int s, int t){
	add(d, s, t);
}
void addiu(int *d,int s, int t){
	
}