#include <stdio.h>
#include <stdlib.h>

typedef struct ConditionCodes {

    uint8_t    zero:1;
    uint8_t    sign:1;
    uint8_t    p:1;
    uint8_t    carry:1;
    uint8_t    ac:1;
    uint8_t    pad:3;

} ConditionCodes;

typedef struct State8080 {

    uint8_t    a;
    uint8_t    b;
    uint8_t    c;
    uint8_t    d;
    uint8_t    e;
    uint8_t    h;
    uint8_t    l;
    uint16_t   sp;
    uint16_t   pc;
    uint8_t    *memory;
    struct     ConditionCodes   cc;
    uint8_t    int_enable;

} State8080;


 void UnimplementedInstruction(State8080* state)
   {
    printf ("Error: Unimplemented instruction\n");
    exit(1);
   }

int dissasemble_8080(State8080* state){

    switch(*(state->memory + state->pc)){

        case 0x00: printf("NOP"); state->pc++; break;
        case 0x01: printf("LXI B $%02x%02x", *(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0x02: printf("STAX B"); state->pc++; break;
        case 0x03: printf("INX B");
            inx(state->b,state->c);
            break;

        case 0x04: printf("INR B"); state->pc++; break;
        case 0x05: printf("DCR B"); state->pc++; break;
        case 0x06: printf("MVI B $%02x",*(state->memory + state->pc +1)); state->pc+=2; break;
        case 0x07: printf("RLC"); state->pc++; break;
        case 0x08: printf("NOP"); state->pc++; break;
        case 0x09: printf("DAD B"); state->pc++; break;
        case 0x0a: printf("LDAX B"); state->pc++; break;
        case 0x0b: printf("DCX B"); state->pc++; break;
        case 0x0c: printf("INR C"); state->pc++; break;
        case 0x0d: printf("DCR C"); state->pc++; break;
        case 0x0e: printf("MVI C $%02x",*(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0x0f: printf("RRC"); state->pc++; break;

        case 0x10: printf("NOP"); state->pc++; break;
        case 0x11: printf("LXI D,#$%02x%02x", *(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0x12: printf("STAX D"); state->pc++; break;
        case 0x13: printf("INX D");

            inx(state->d,state->e);
            break;

        case 0x14: printf("INR D"); state->pc++; break;
        case 0x15: printf("DCR D"); state->pc++; break;
        case 0x16: printf("MVI D,#$%02x", *(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0x17: printf("RAL"); state->pc++; break;
        case 0x18: printf("NOP"); state->pc++; break;
        case 0x19: printf("DAD D"); state->pc++; break;
        case 0x1a: printf("LDAX D"); state->pc++; break;
        case 0x1b: printf("DCX D"); state->pc++; break;
        case 0x1c: printf("INR E"); state->pc++; break;
        case 0x1d: printf("DCR E"); state->pc++; break;
        case 0x1e: printf("MVI E,#$%02x", *(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0x1f: printf("RAR"); state->pc++; break;

        case 0x20: printf("NOP"); state->pc++; break;
        case 0x21: printf("LXI H,#$%02x%02x", *(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0x22: printf("SHLD $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0x23: printf("INX H");
            inx(state->h,state->l);
            break;

        case 0x24: printf("INR H"); state->pc++; break;
        case 0x25: printf("DCR H"); state->pc++; break;
        case 0x26: printf("MVI H,#$%02x",*(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0x27: printf("DAA"); state->pc++; break;
        case 0x28: printf("NOP"); state->pc++; break;
        case 0x29: printf("DAD H"); state->pc++; break;
        case 0x2a: printf("LHLD $%02x%02x",*(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0x2b: printf("DCX H"); state->pc++; break;
        case 0x2c: printf("INR L"); state->pc++; break;
        case 0x2d: printf("DCR L"); state->pc++; break;
        case 0x2e: printf("MVI L,#$%02x", *(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0x2f: printf("CMA"); state->pc++; break;

        case 0x30: printf("NOP"); state->pc++; break;
        case 0x31: printf("LXI SP,#$%02x%02x", *(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0x32: printf("STA $%02x%02x", *(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0x33: printf("INX SP");
            state->sp++;
            state->pc++;
            break;

        case 0x34: printf("INR M"); state->pc++; break;
        case 0x35: printf("DCR M"); state->pc++; break;
        case 0x36: printf("MVI    M,#$%02x", *(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0x37: printf("STC"); state->pc++; break;
        case 0x38: printf("NOP"); state->pc++; break;
        case 0x39: printf("DAD SP"); state->pc++; break;
        case 0x3a: printf("LDA $%02x%02x", *(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0x3b: printf("DCX    SP"); state->pc++; break;
        case 0x3c: printf("INR    A"); state->pc++; break;
        case 0x3d: printf("DCR    A"); state->pc++; break;
        case 0x3e: printf("MVI    A,#$%02x", *(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0x3f: printf("CMC"); state->pc++; break;

        case 0x40: printf("MOV    B,B"); state->pc++; break;
        case 0x41: printf("MOV    B,C"); state->pc++; break;
        case 0x42: printf("MOV    B,D"); state->pc++; break;
        case 0x43: printf("MOV    B,E"); state->pc++; break;
        case 0x44: printf("MOV    B,H"); state->pc++; break;
        case 0x45: printf("MOV    B,L"); state->pc++; break;
        case 0x46: printf("MOV    B,M"); state->pc++; break;
        case 0x47: printf("MOV    B,A"); state->pc++; break;
        case 0x48: printf("MOV    C,B"); state->pc++; break;
        case 0x49: printf("MOV    C,C"); state->pc++; break;
        case 0x4a: printf("MOV    C,D"); state->pc++; break;
        case 0x4b: printf("MOV    C,E"); state->pc++; break;
        case 0x4c: printf("MOV    C,H"); state->pc++; break;
        case 0x4d: printf("MOV    C,L"); state->pc++; break;
        case 0x4e: printf("MOV    C,M"); state->pc++; break;
        case 0x4f: printf("MOV    C,A"); state->pc++; break;

        case 0x50: printf("MOV    D,B"); state->pc++; break;
        case 0x51: printf("MOV    D,C"); state->pc++; break;
        case 0x52: printf("MOV    D,D"); state->pc++; break;
        case 0x53: printf("MOV    D.E"); state->pc++; break;
        case 0x54: printf("MOV    D,H"); state->pc++; break;
        case 0x55: printf("MOV    D,L"); state->pc++; break;
        case 0x56: printf("MOV    D,M"); state->pc++; break;
        case 0x57: printf("MOV    D,A"); state->pc++; break;
        case 0x58: printf("MOV    E,B"); state->pc++; break;
        case 0x59: printf("MOV    E,C"); state->pc++; break;
        case 0x5a: printf("MOV    E,D"); state->pc++; break;
        case 0x5b: printf("MOV    E,E"); state->pc++; break;
        case 0x5c: printf("MOV    E,H"); state->pc++; break;
        case 0x5d: printf("MOV    E,L"); state->pc++; break;
        case 0x5e: printf("MOV    E,M"); state->pc++; break;
        case 0x5f: printf("MOV    E,A"); state->pc++; break;

        case 0x60: printf("MOV    H,B"); state->pc++; break;
        case 0x61: printf("MOV    H,C"); state->pc++; break;
        case 0x62: printf("MOV    H,D"); state->pc++; break;
        case 0x63: printf("MOV    H.E"); state->pc++; break;
        case 0x64: printf("MOV    H,H"); state->pc++; break;
        case 0x65: printf("MOV    H,L"); state->pc++; break;
        case 0x66: printf("MOV    H,M"); state->pc++; break;
        case 0x67: printf("MOV    H,A"); state->pc++; break;
        case 0x68: printf("MOV    L,B"); state->pc++; break;
        case 0x69: printf("MOV    L,C"); state->pc++; break;
        case 0x6a: printf("MOV    L,D"); state->pc++; break;
        case 0x6b: printf("MOV    L,E"); state->pc++; break;
        case 0x6c: printf("MOV    L,H"); state->pc++; break;
        case 0x6d: printf("MOV    L,L"); state->pc++; break;
        case 0x6e: printf("MOV    L,M"); state->pc++; break;
        case 0x6f: printf("MOV    L,A"); state->pc++; break;

        case 0x70: printf("MOV    M,B"); state->pc++; break;
        case 0x71: printf("MOV    M,C"); state->pc++; break;
        case 0x72: printf("MOV    M,D"); state->pc++; break;
        case 0x73: printf("MOV    M.E"); state->pc++; break;
        case 0x74: printf("MOV    M,H"); state->pc++; break;
        case 0x75: printf("MOV    M,L"); state->pc++; break;
        case 0x76: printf("HLT");        state->pc++; break;
        case 0x77: printf("MOV    M,A"); state->pc++; break;
        case 0x78: printf("MOV    A,B"); state->pc++; break;
        case 0x79: printf("MOV    A,C"); state->pc++; break;
        case 0x7a: printf("MOV    A,D"); state->pc++; break;
        case 0x7b: printf("MOV    A,E"); state->pc++; break;
        case 0x7c: printf("MOV    A,H"); state->pc++; break;
        case 0x7d: printf("MOV    A,L"); state->pc++; break;
        case 0x7e: printf("MOV    A,M"); state->pc++; break;
        case 0x7f: printf("MOV    A,A"); state->pc++; break;

        case 0x80: printf("ADD    B");
            add((uint16_t)state->b);
            break;

        case 0x81: printf("ADD    C");
            add((uint16_t)state->c);
            break;

        case 0x82: printf("ADD    D");
            add((uint16_t)state->d);
            break;
        case 0x83: printf("ADD    E");
            add((uint16_t)state->e);
            break;
        case 0x84: printf("ADD    H");
            add((uint16_t)state->h);
            break;
        case 0x85: printf("ADD    L");
            add((uint16_t)state->l);
            break;
        case 0x86: printf("ADD    M");
            add((uint16_t)(state->h<<8) | (state->l));
            break;
        case 0x87: printf("ADD    A");
            add((uint16_t)state->a);
            break;
        case 0x88: printf("ADC    B"); state->pc++; break;
        case 0x89: printf("ADC    C"); state->pc++; break;
        case 0x8a: printf("ADC    D"); state->pc++; break;
        case 0x8b: printf("ADC    E"); state->pc++; break;
        case 0x8c: printf("ADC    H"); state->pc++; break;
        case 0x8d: printf("ADC    L"); state->pc++; break;
        case 0x8e: printf("ADC    M"); state->pc++; break;
        case 0x8f: printf("ADC    A"); state->pc++; break;

        case 0x90: printf("SUB    B");
            sub(state->b);
            break;

        case 0x91: printf("SUB    C");
            sub(state->c);
            break;

        case 0x92: printf("SUB    D");
            sub(state->d);
            break;

        case 0x93: printf("SUB    E");
            sub(state->e);
            break;

        case 0x94: printf("SUB    H");
            sub(state->h);
            break;

        case 0x95: printf("SUB    L");
            sub(state->l);
            break;

        case 0x96: printf("SUB    M");
            sub((state->h<<8) | (state->l));
            break;

        case 0x97: printf("SUB    A");
            sub(state->a);
            break;

        case 0x98: printf("SBB    B"); state->pc++; break;
        case 0x99: printf("SBB    C"); state->pc++; break;
        case 0x9a: printf("SBB    D"); state->pc++; break;
        case 0x9b: printf("SBB    E"); state->pc++; break;
        case 0x9c: printf("SBB    H"); state->pc++; break;
        case 0x9d: printf("SBB    L"); state->pc++; break;
        case 0x9e: printf("SBB    M"); state->pc++; break;
        case 0x9f: printf("SBB    A"); state->pc++; break;

        case 0xa0: printf("ANA    B"); state->pc++; break;
        case 0xa1: printf("ANA    C"); state->pc++; break;
        case 0xa2: printf("ANA    D"); state->pc++; break;
        case 0xa3: printf("ANA    E"); state->pc++; break;
        case 0xa4: printf("ANA    H"); state->pc++; break;
        case 0xa5: printf("ANA    L"); state->pc++; break;
        case 0xa6: printf("ANA    M"); state->pc++; break;
        case 0xa7: printf("ANA    A"); state->pc++; break;
        case 0xa8: printf("XRA    B"); state->pc++; break;
        case 0xa9: printf("XRA    C"); state->pc++; break;
        case 0xaa: printf("XRA    D"); state->pc++; break;
        case 0xab: printf("XRA    E"); state->pc++; break;
        case 0xac: printf("XRA    H"); state->pc++; break;
        case 0xad: printf("XRA    L"); state->pc++; break;
        case 0xae: printf("XRA    M"); state->pc++; break;
        case 0xaf: printf("XRA    A"); state->pc++; break;

        case 0xb0: printf("ORA    B"); state->pc++; break;
        case 0xb1: printf("ORA    C"); state->pc++; break;
        case 0xb2: printf("ORA    D"); state->pc++; break;
        case 0xb3: printf("ORA    E"); state->pc++; break;
        case 0xb4: printf("ORA    H"); state->pc++; break;
        case 0xb5: printf("ORA    L"); state->pc++; break;
        case 0xb6: printf("ORA    M"); state->pc++; break;
        case 0xb7: printf("ORA    A"); state->pc++; break;
        case 0xb8: printf("CMP    B"); state->pc++; break;
        case 0xb9: printf("CMP    C"); state->pc++; break;
        case 0xba: printf("CMP    D"); state->pc++; break;
        case 0xbb: printf("CMP    E"); state->pc++; break;
        case 0xbc: printf("CMP    H"); state->pc++; break;
        case 0xbd: printf("CMP    L"); state->pc++; break;
        case 0xbe: printf("CMP    M"); state->pc++; break;
        case 0xbf: printf("CMP    A"); state->pc++; break;

        case 0xc0: printf("RNZ"); state->pc++; break;
        case 0xc1: printf("POP    B"); state->pc++; break;
        case 0xc2: printf("JNZ    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xc3: printf("JMP    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xc4: printf("CNZ    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xc5: printf("PUSH   B"); state->pc++; break;
        case 0xc6: printf("ADI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0xc7: printf("RST    0"); state->pc++; break;
        case 0xc8: printf("RZ"); state->pc++; break;
        case 0xc9: printf("RET"); state->pc++; break;
        case 0xca: printf("JZ     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xcb: printf("JMP    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xcc: printf("CZ     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xcd: printf("CALL   $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xce: printf("ACI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0xcf: printf("RST    1"); state->pc++; break;

        case 0xd0: printf("RNC"); state->pc++; break;
        case 0xd1: printf("POP    D"); state->pc++; break;
        case 0xd2: printf("JNC    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xd3: printf("OUT    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0xd4: printf("CNC    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xd5: printf("PUSH   D"); state->pc++; break;
        case 0xd6: printf("SUI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0xd7: printf("RST    2"); state->pc++; break;
        case 0xd8: printf("RC");  state->pc++; break;
        case 0xd9: printf("RET"); state->pc++; break;
        case 0xda: printf("JC     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xdb: printf("IN     #$%02x",*(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0xdc: printf("CC     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xdd: printf("CALL   $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xde: printf("SBI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0xdf: printf("RST    3"); state->pc++; break;

        case 0xe0: printf("RPO"); state->pc++; break;
        case 0xe1: printf("POP    H"); state->pc++; break;
        case 0xe2: printf("JPO    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xe3: printf("XTHL");state->pc++; break;
        case 0xe4: printf("CPO    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xe5: printf("PUSH   H"); state->pc++; break;
        case 0xe6: printf("ANI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0xe7: printf("RST    4"); state->pc++; break;
        case 0xe8: printf("RPE"); state->pc++; break;
        case 0xe9: printf("state->pcHL");state->pc++; break;
        case 0xea: printf("JPE    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xeb: printf("XCHG"); state->pc++; break;
        case 0xec: printf("CPE     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xed: printf("CALL   $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xee: printf("XRI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0xef: printf("RST    5"); state->pc++; break;

        case 0xf0: printf("RP");  state->pc++; break;
        case 0xf1: printf("POP    PSW"); state->pc++; break;
        case 0xf2: printf("JP     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xf3: printf("DI");  state->pc++; break;
        case 0xf4: printf("CP     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xf5: printf("PUSH   PSW"); state->pc++; break;
        case 0xf6: printf("ORI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2; break;
        case 0xf7: printf("RST    6"); state->pc++; break;
        case 0xf8: printf("RM");  state->pc++; break;
        case 0xf9: printf("SPHL");state->pc++; break;
        case 0xfa: printf("JM     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xfb: printf("EI");  state->pc++; break;
        case 0xfc: printf("CM     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xfd: printf("CALL   $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3; break;
        case 0xfe: printf("CPI    #$%02x",*(state->memory + state->pc + 1));state->pc+=2; break;
        case 0xff: printf("RST 7"); state->pc++; break;
    }
    return state->pc;

}

uint8_t parity(uint8_t val){

    int counter = 0;
    int index;
    for(index = 1;index<9;index++){
        if((val & 0x01) == 1)
            counter++;

        val = val >> 1;
    }

    if((counter % 2) == 0)
        return 1;
    else
        return 0;
}


void inx(uint8_t toInx, uint8_t toInxNext){

    (uint16_t) new_val = ((uint16_t)(toInx << 8)) | ((uint16_t)(toInxNext));
    new_val = new_val + 1;
    toInx = (uint8_t)((new_val & 0xff00) >> 8);
    toInxNext = (uint8_t)(new_val & 0xff);
    state->pc++;
}


void sub(uint8_t toSub){

    uint8_t answer = state->a - state->b;
    state->cc.zero = (answer & 0xff) == 0;
    state->cc.sign = (answer & 0x80) >> 7;

    state->cc.parity = parity(answer);

    state->a = answer;
    state->pc++;

}



void add(uint16_t toAdd){

    uint16_t answer = (uint16_t)state->a + toAdd;
    state->cc.zero = ((answer & 0xff) == 0);
    state->cc.carry = (answer > 0xff);
    state->cc.sign = ((answer & 0x80) >> 7);

    state->cc.parity = parity(answer);

    state->a = answer & 0xff;
    state->pc++;
}

State8080* InitMemory(){
    State8080* state = calloc(1,sizeof(State8080));
    state->memory = malloc(0x10000); //16k
    return state;
}


void ReadFileIntoMemory(State8080 *state,char* filename, uint32_t offset){

    FILE *fp;
    int c;
    fp = fopen (filename, "rb");

    fseek(fp,0,SEEK_END);
    long fsize = ftell(fp);
    fseek(fp,0,SEEK_SET);

    uint8_t *buffer = &state->memory[offset];

    c = fread(state->memory,sizeof(uint8_t),fsize,fp);

    fclose(fp);

}


int main(int argc, char const *argv[])
{

    State8080* state = InitMemory();

    ReadFileIntoMemory(state,"invaders.h",0);
    ReadFileIntoMemory(state,"invaders.g",0x800);
    ReadFileIntoMemory(state,"invaders.f",0x1000);
    ReadFileIntoMemory(state,"invaders.e",0x1800);

    while(state->pc != (fsize-1))
        state->pc = dissasemble_8080(state->memory,state->pc);

    return 0;
}


