void letext(const char *argv[], int mem[]);
void ledata(const char *argv[], int mem[]);
void tipoR(int bancoReg[], int rs, int rt, int rd, int shamt, int funct, int *HI, int *LO, int *PC);
void tipoI(int bancoReg[], int opcode, int rs, int rt, int immediate);
void tipoJ(int mem[], int bancoReg[], int opcode, int immediate, int *PC);
//Tipo R
void add(int bancoReg[], int rs, int rt, int rd);
void sub(int bancoReg[], int rs, int rt, int rd);
void mult(int bancoReg[], int rs, int rt,int *HI, int *LO);
void divv(int bancoReg[], int rs, int rt,int *HI, int *LO);
void mfhi(int bancoReg[], int rd, int *HI);
void mflo(int bancoReg[], int rd, int *LO);
void and(int bancoReg[], int rs, int rt, int rd);
void or(int bancoReg[], int rs, int rt, int rd);
void slt(int bancoReg[], int rs, int rt, int rd);
void sll(int bancoReg[], int rt, int rd, int shamt);
void srl(int bancoReg[], int rt, int rd, int shamt);
void jr(int bancoReg[], int rs, int *PC);
//Tipo I
void addi(int bancoReg[], int rs, int immediate, int rt);
void addiu(int bancoReg[], int rs, int rt, int immediate);
//Tipo J
//funçoes acima terminadas
void j(int mem[], int *PC, int immediate);
void jal(int mem[], int bancoReg[], int immediate, int *PC);
void lw(int *mem, int C, int s, int *t);
void lh(int *mem, int C, int s, int *t);
void lb(int *mem, int C, int s, int *t);
void sw(int *mem, int C, int s, int *t);
void sh(int *mem, int C, int s, int *t);
void sb(int *mem, int C, int s, int *t);
void lui(int *d, int C);
void andi(int *d, int s, int t);
void ori(int *d, int s, int t);
void slti(int *d, int s, int t);
void beq(int *PC, int s, int t, int C);
void bne(int *PC, int s, int t, int C);
void syscall(int bancoReg[],int *EXIT);