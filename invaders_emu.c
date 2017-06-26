#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct ConditionCodes {

    uint8_t    zero:1;
    uint8_t    sign:1;
    uint8_t    parity:1;
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

State8080* state;

 void UnimplementedInstruction(State8080* state)
   {
    printf ("Error: Unimplemented instruction\n");
    exit(1);
   }

int dissasemble_8080(State8080* state){

    switch(*(state->memory + state->pc)){

        case 0x00: printf("NOP"); state->pc++;UnimplementedInstruction(state); break;
        case 0x01: printf("LXI B $%02x%02x", *(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0x02: printf("STAX B"); state->pc++;UnimplementedInstruction(state); break;
        case 0x03: printf("INX B");
            dcxInx(state->b,state->c,'i');
            break;

        case 0x04: printf("INR B"); state->pc++;UnimplementedInstruction(state); break;
        case 0x05: printf("DCR B"); state->pc++;UnimplementedInstruction(state); break;
        case 0x06: printf("MVI B $%02x",*(state->memory + state->pc +1)); 

            mov(state->b,state->memory[state->pc+1]);
            state->pc+=2; 
            break;
        
        case 0x07: printf("RLC"); state->pc++;UnimplementedInstruction(state); break;
        case 0x08: printf("NOP"); state->pc++;UnimplementedInstruction(state); break;
        case 0x09: printf("DAD B");

            dad(state->b,state->c);
            break;

        case 0x0a: printf("LDAX B"); state->pc++;UnimplementedInstruction(state); break;
        case 0x0b: printf("DCX B");
            dcxInx(state->b,state->c,'d');
            break;

        case 0x0c: printf("INR C"); state->pc++;UnimplementedInstruction(state); break;
        case 0x0d: printf("DCR C"); state->pc++;UnimplementedInstruction(state); break;
        case 0x0e: printf("MVI C $%02x",*(state->memory + state->pc + 1)); 

            mov(state->c,state->memory[state->pc+1]);
            state->pc+=2; 
            break;
        
        case 0x0f: printf("RRC"); state->pc++;UnimplementedInstruction(state); break;

        case 0x10: printf("NOP"); state->pc++;UnimplementedInstruction(state); break;
        case 0x11: printf("LXI D,#$%02x%02x", *(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0x12: printf("STAX D"); state->pc++;UnimplementedInstruction(state); break;
        case 0x13: printf("INX D");

            dcxInx(state->d,state->e,'i');
            break;

        case 0x14: printf("INR D"); state->pc++;UnimplementedInstruction(state); break;
        case 0x15: printf("DCR D"); state->pc++;UnimplementedInstruction(state); break;
        case 0x16: printf("MVI D,#$%02x", *(state->memory + state->pc + 1)); 
            mov(state->d,state->memory[state->pc+1]);
            state->pc+=2; 
            break;
        
        case 0x17: printf("RAL"); state->pc++;UnimplementedInstruction(state); break;
        case 0x18: printf("NOP"); state->pc++;UnimplementedInstruction(state); break;
        case 0x19: printf("DAD D");

            dad(state->d,state->e);
            break;

        case 0x1a: printf("LDAX D"); state->pc++;UnimplementedInstruction(state); break;
        case 0x1b: printf("DCX D");
            dcxInx(state->d,state->e,'d');
            break;
        case 0x1c: printf("INR E"); state->pc++;UnimplementedInstruction(state); break;
        case 0x1d: printf("DCR E"); state->pc++;UnimplementedInstruction(state); break;
        case 0x1e: printf("MVI E,#$%02x", *(state->memory + state->pc + 1)); 

            mov(state->e,state->memory[state->pc+1]);
            state->pc+=2; 
            break;
        
        case 0x1f: printf("RAR"); state->pc++;UnimplementedInstruction(state); break;

        case 0x20: printf("NOP"); state->pc++;UnimplementedInstruction(state); break;
        case 0x21: printf("LXI H,#$%02x%02x", *(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0x22: printf("SHLD $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0x23: printf("INX H");
            dcxInx(state->h,state->l,'i');
            break;

        case 0x24: printf("INR H"); state->pc++;UnimplementedInstruction(state); break;
        case 0x25: printf("DCR H"); state->pc++;UnimplementedInstruction(state); break;
        case 0x26: printf("MVI H,#$%02x",*(state->memory + state->pc + 1)); 
            
            mov(state->h,state->memory[state->pc+1]);
            state->pc+=2; 
            break;
        
        case 0x27: printf("DAA"); state->pc++;UnimplementedInstruction(state); break;
        case 0x28: printf("NOP"); state->pc++;UnimplementedInstruction(state); break;
        case 0x29: printf("DAD H");

            dad(state->h,state->l);
            break;

        case 0x2a: printf("LHLD $%02x%02x",*(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0x2b: printf("DCX H");
            dcxInx(state->h,state->l,'d');
            break;
        case 0x2c: printf("INR L"); state->pc++;UnimplementedInstruction(state); break;
        case 0x2d: printf("DCR L"); state->pc++;UnimplementedInstruction(state); break;
        case 0x2e: printf("MVI L,#$%02x", *(state->memory + state->pc + 1)); 
            
            mov(state->l,state->memory[state->pc+1]);
            state->pc+=2; 
            break;
        
        case 0x2f: printf("CMA"); state->pc++;UnimplementedInstruction(state); break;

        case 0x30: printf("NOP"); state->pc++;UnimplementedInstruction(state); break;
        case 0x31: printf("LXI SP,#$%02x%02x", *(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0x32: printf("STA $%02x%02x", *(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0x33: printf("INX SP");
            state->sp++;
            state->pc++;
            break;

        case 0x34: printf("INR M"); state->pc++;UnimplementedInstruction(state); break;
        case 0x35: printf("DCR M"); state->pc++;UnimplementedInstruction(state); break;
        case 0x36: printf("MVI    M,#$%02x", *(state->memory + state->pc + 1)); 

            state->memory[(state->h<<8) | state->l] = state->memory[state->pc + 1];
            state->pc+=2; 
            break;
        
        case 0x37: printf("STC"); state->pc++;UnimplementedInstruction(state); break;
        case 0x38: printf("NOP"); state->pc++;UnimplementedInstruction(state); break;
        case 0x39: printf("DAD SP");
            
            dad((uint8_t)((state->sp & 0xff00) >> 8),(uint8_t)(state->sp & 0x00ff));
            break;
        
        case 0x3a: printf("LDA $%02x%02x", *(state->memory + state->pc + 2), *(state->memory + state->pc + 1)); 
            
            uint16_t offset = (state->memory[state->pc + 2]<<8) | state->memory[state->pc + 1];   //2 is MSB
            state->memory[offset]; 
            state->pc+=3; 
            break;
        
        case 0x3b: printf("DCX    SP");
            
            state->sp--;
            state->pc++;
            break;

        case 0x3c: printf("INR    A"); state->pc++;UnimplementedInstruction(state); break;
        case 0x3d: printf("DCR    A"); state->pc++;UnimplementedInstruction(state); break;
        case 0x3e: printf("MVI    A,#$%02x", *(state->memory + state->pc + 1)); 

            mov(state->a, state->memory[state->pc + 1]);
            state->pc+=2; 
            break;
        
        case 0x3f: printf("CMC"); state->pc++;UnimplementedInstruction(state); break;

        case 0x40: printf("MOV    B,B"); state->pc++;UnimplementedInstruction(state); break;

        case 0x41: printf("MOV    B,C"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x42: printf("MOV    B,D"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x43: printf("MOV    B,E"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x44: printf("MOV    B,H"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x45: printf("MOV    B,L"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x46: printf("MOV    B,M"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x47: printf("MOV    B,A"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x48: printf("MOV    C,B"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x49: printf("MOV    C,C"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x4a: printf("MOV    C,D"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x4b: printf("MOV    C,E"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x4c: printf("MOV    C,H"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x4d: printf("MOV    C,L"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x4e: printf("MOV    C,M"); 

            movM(state->c);
            state->pc++; 
            break;
        
        case 0x4f: printf("MOV    C,A"); state->pc++;UnimplementedInstruction(state); break;

        case 0x50: printf("MOV    D,B"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x51: printf("MOV    D,C"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x52: printf("MOV    D,D"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x53: printf("MOV    D.E"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x54: printf("MOV    D,H"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x55: printf("MOV    D,L"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x56: printf("MOV    D,M"); 

            movM(state->d);
            state->pc++; 
            break;
        
        case 0x57: printf("MOV    D,A"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x58: printf("MOV    E,B"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x59: printf("MOV    E,C"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x5a: printf("MOV    E,D"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x5b: printf("MOV    E,E"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x5c: printf("MOV    E,H"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x5d: printf("MOV    E,L"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x5e: printf("MOV    E,M"); 
            
            movM(state->e);
            state->pc++; 
            break;
        
        case 0x5f: printf("MOV    E,A"); state->pc++;UnimplementedInstruction(state); break;

        case 0x60: printf("MOV    H,B"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x61: printf("MOV    H,C"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x62: printf("MOV    H,D"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x63: printf("MOV    H,E"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x64: printf("MOV    H,H"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x65: printf("MOV    H,L"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x66: printf("MOV    H,M"); 
            
            movM(state->h);
            state->pc++; 
            break;
        
        case 0x67: printf("MOV    H,A"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x68: printf("MOV    L,B"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x69: printf("MOV    L,C"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x6a: printf("MOV    L,D"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x6b: printf("MOV    L,E"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x6c: printf("MOV    L,H"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x6d: printf("MOV    L,L"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x6e: printf("MOV    L,M"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x6f: printf("MOV    L,A"); 
            
            mov(state->l,state->a);
            state->pc++; 
            break;


        case 0x70: printf("MOV    M,B"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x71: printf("MOV    M,C"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x72: printf("MOV    M,D"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x73: printf("MOV    M.E"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x74: printf("MOV    M,H"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x75: printf("MOV    M,L"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x76: printf("HLT");        

            exit(0);
        
        case 0x77: printf("MOV    M,A"); 
            
            uint16_t newVal = (state->h<<8) | (state->l);
            state->memory[newVal] = state->a;
            state->pc++; 
            break;
        
        case 0x78: printf("MOV    A,B"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x79: printf("MOV    A,C"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x7a: printf("MOV    A,D"); 
            
            mov(state->a,state->d);
            state->pc++; 
            break;
        
        case 0x7b: printf("MOV    A,E"); 
            mov(state->a,state->e);
            state->pc++; 
            break;
        
        case 0x7c: printf("MOV    A,H"); 
            mov(state->a,state->h);
            state->pc++; 
            break;
        
        case 0x7d: printf("MOV    A,L"); state->pc++;UnimplementedInstruction(state); break;
        
        case 0x7e: printf("MOV    A,M");

            movM(state->a); 
            state->pc++; 
            break;
        
        case 0x7f: printf("MOV    A,A"); state->pc++;UnimplementedInstruction(state); break;

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
        case 0x88: printf("ADC    B"); state->pc++;UnimplementedInstruction(state); break;
        case 0x89: printf("ADC    C"); state->pc++;UnimplementedInstruction(state); break;
        case 0x8a: printf("ADC    D"); state->pc++;UnimplementedInstruction(state); break;
        case 0x8b: printf("ADC    E"); state->pc++;UnimplementedInstruction(state); break;
        case 0x8c: printf("ADC    H"); state->pc++;UnimplementedInstruction(state); break;
        case 0x8d: printf("ADC    L"); state->pc++;UnimplementedInstruction(state); break;
        case 0x8e: printf("ADC    M"); state->pc++;UnimplementedInstruction(state); break;
        case 0x8f: printf("ADC    A"); state->pc++;UnimplementedInstruction(state); break;

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

        case 0x98: printf("SBB    B"); state->pc++;UnimplementedInstruction(state); break;
        case 0x99: printf("SBB    C"); state->pc++;UnimplementedInstruction(state); break;
        case 0x9a: printf("SBB    D"); state->pc++;UnimplementedInstruction(state); break;
        case 0x9b: printf("SBB    E"); state->pc++;UnimplementedInstruction(state); break;
        case 0x9c: printf("SBB    H"); state->pc++;UnimplementedInstruction(state); break;
        case 0x9d: printf("SBB    L"); state->pc++;UnimplementedInstruction(state); break;
        case 0x9e: printf("SBB    M"); state->pc++;UnimplementedInstruction(state); break;
        case 0x9f: printf("SBB    A"); state->pc++;UnimplementedInstruction(state); break;

        case 0xa0: printf("ANA    B"); state->pc++;UnimplementedInstruction(state); break;
        case 0xa1: printf("ANA    C"); state->pc++;UnimplementedInstruction(state); break;
        case 0xa2: printf("ANA    D"); state->pc++;UnimplementedInstruction(state); break;
        case 0xa3: printf("ANA    E"); state->pc++;UnimplementedInstruction(state); break;
        case 0xa4: printf("ANA    H"); state->pc++;UnimplementedInstruction(state); break;
        case 0xa5: printf("ANA    L"); state->pc++;UnimplementedInstruction(state); break;
        case 0xa6: printf("ANA    M"); state->pc++;UnimplementedInstruction(state); break;
        case 0xa7: printf("ANA    A"); 
            
            ana(state->a);
            state->pc++; 
            break;

        case 0xa8: printf("XRA    B"); state->pc++;UnimplementedInstruction(state); break;
        case 0xa9: printf("XRA    C"); state->pc++;UnimplementedInstruction(state); break;
        case 0xaa: printf("XRA    D"); state->pc++;UnimplementedInstruction(state); break;
        case 0xab: printf("XRA    E"); state->pc++;UnimplementedInstruction(state); break;
        case 0xac: printf("XRA    H"); state->pc++;UnimplementedInstruction(state); break;
        case 0xad: printf("XRA    L"); state->pc++;UnimplementedInstruction(state); break;
        case 0xae: printf("XRA    M"); state->pc++;UnimplementedInstruction(state); break;
        case 0xaf: printf("XRA    A"); state->pc++;UnimplementedInstruction(state); break;

        case 0xb0: printf("ORA    B"); state->pc++;UnimplementedInstruction(state); break;
        case 0xb1: printf("ORA    C"); state->pc++;UnimplementedInstruction(state); break;
        case 0xb2: printf("ORA    D"); state->pc++;UnimplementedInstruction(state); break;
        case 0xb3: printf("ORA    E"); state->pc++;UnimplementedInstruction(state); break;
        case 0xb4: printf("ORA    H"); state->pc++;UnimplementedInstruction(state); break;
        case 0xb5: printf("ORA    L"); state->pc++;UnimplementedInstruction(state); break;
        case 0xb6: printf("ORA    M"); state->pc++;UnimplementedInstruction(state); break;
        case 0xb7: printf("ORA    A"); state->pc++;UnimplementedInstruction(state); break;
        case 0xb8: printf("CMP    B"); state->pc++;UnimplementedInstruction(state); break;
        case 0xb9: printf("CMP    C"); state->pc++;UnimplementedInstruction(state); break;
        case 0xba: printf("CMP    D"); state->pc++;UnimplementedInstruction(state); break;
        case 0xbb: printf("CMP    E"); state->pc++;UnimplementedInstruction(state); break;
        case 0xbc: printf("CMP    H"); state->pc++;UnimplementedInstruction(state); break;
        case 0xbd: printf("CMP    L"); state->pc++;UnimplementedInstruction(state); break;
        case 0xbe: printf("CMP    M"); state->pc++;UnimplementedInstruction(state); break;
        case 0xbf: printf("CMP    A"); state->pc++;UnimplementedInstruction(state); break;

        case 0xc0: printf("RNZ"); state->pc++;UnimplementedInstruction(state); break;
        case 0xc1: printf("POP    B"); 
            
            pop(state->b,state->c);
            state->pc++; 
            break;

        case 0xc2: printf("JNZ    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); 
          
            jnz((state->memory[state->pc + 2]) << 8 | state->memory[state->pc+1]);
            break;
        

        case 0xc3: printf("JMP    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1));
            
            jmp((state->memory[state->pc + 2]) << 8 | state->memory[state->pc+1]);
            break;
        

        case 0xc4: printf("CNZ    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xc5: printf("PUSH   B"); 
            
            push(state->b,state->c);
            state->pc++; 
            break;
        
        case 0xc6: printf("ADI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2;UnimplementedInstruction(state); break;
        case 0xc7: printf("RST    0"); state->pc++;UnimplementedInstruction(state); break;
        case 0xc8: printf("RZ"); state->pc++;UnimplementedInstruction(state); break;
        case 0xc9: printf("RET"); 

            ret(); 
            break;
        
        case 0xca: printf("JZ     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xcb: printf("JMP    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); 
            
            jmp((state->memory[state->pc + 2]) << 8 | state->memory[state->pc+1]);
            break;
        
        case 0xcc: printf("CZ     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xcd: printf("CALL   $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); 

            call(state->pc + 3);
            break;

        case 0xce: printf("ACI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2;UnimplementedInstruction(state); break;
        case 0xcf: printf("RST    1"); state->pc++;UnimplementedInstruction(state); break;

        case 0xd0: printf("RNC"); state->pc++;UnimplementedInstruction(state); break;
        case 0xd1: printf("POP    D"); 
            
            pop(state->d,state->e);
            state->pc++; 
            break;

        case 0xd2: printf("JNC    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xd3: printf("OUT    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2;UnimplementedInstruction(state); break;
        case 0xd4: printf("CNC    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xd5: printf("PUSH   D"); 
            
            push(state->d,state->e);
            state->pc++; 
            break;

        case 0xd6: printf("SUI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2;UnimplementedInstruction(state); break;
        case 0xd7: printf("RST    2"); state->pc++;UnimplementedInstruction(state); break;
        case 0xd8: printf("RC");  state->pc++;UnimplementedInstruction(state); break;
        case 0xd9: printf("RET"); 
        
            ret(); 
            break;
        
        case 0xda: printf("JC     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xdb: printf("IN     #$%02x",*(state->memory + state->pc + 1)); state->pc+=2;UnimplementedInstruction(state); break;
        case 0xdc: printf("CC     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xdd: printf("CALL   $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); 

            call(state->pc + 3);
            break;
        
        case 0xde: printf("SBI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2;UnimplementedInstruction(state); break;
        case 0xdf: printf("RST    3"); state->pc++;UnimplementedInstruction(state); break;

        case 0xe0: printf("RPO"); state->pc++;UnimplementedInstruction(state); break;
        case 0xe1: printf("POP    H"); 
            
            pop(state->h,state->l);
            state->pc++; 
            break;
        
        case 0xe2: printf("JPO    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xe3: printf("XTHL");state->pc++;UnimplementedInstruction(state); break;
        case 0xe4: printf("CPO    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xe5: printf("PUSH   H"); 
            
            push(state->h,state->l);
            state->pc++; 
            break;

        case 0xe6: printf("ANI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2;UnimplementedInstruction(state); break;
        case 0xe7: printf("RST    4"); state->pc++;UnimplementedInstruction(state); break;
        case 0xe8: printf("RPE"); state->pc++;UnimplementedInstruction(state); break;
        case 0xe9: printf("PCHL");state->pc++;UnimplementedInstruction(state); break;
        case 0xea: printf("JPE    $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xeb: printf("XCHG"); state->pc++;UnimplementedInstruction(state); break;
        case 0xec: printf("CPE     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xed: printf("CALL   $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); 
        
            call(state->pc + 3);
            break;
        
        case 0xee: printf("XRI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2;UnimplementedInstruction(state); break;
        case 0xef: printf("RST    5"); state->pc++;UnimplementedInstruction(state); break;

        case 0xf0: printf("RP");  state->pc++;UnimplementedInstruction(state); break;
        case 0xf1: printf("POP    PSW"); 
            
            popPSW();
            state->pc++; 
            break;
        
        case 0xf2: printf("JP     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xf3: printf("DI");  state->pc++;UnimplementedInstruction(state); break;
        case 0xf4: printf("CP     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xf5: printf("PUSH   PSW"); 
            
            pushPSW();    
            state->pc++; 
            break;
        
        case 0xf6: printf("ORI    #$%02x",*(state->memory + state->pc + 1)); state->pc+=2;UnimplementedInstruction(state); break;
        case 0xf7: printf("RST    6"); state->pc++;UnimplementedInstruction(state); break;
        case 0xf8: printf("RM");  state->pc++;UnimplementedInstruction(state); break;
        case 0xf9: printf("SPHL");state->pc++;UnimplementedInstruction(state); break;
        case 0xfa: printf("JM     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xfb: printf("EI");  state->pc++;UnimplementedInstruction(state); break;
        case 0xfc: printf("CM     $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); state->pc+=3;UnimplementedInstruction(state); break;
        case 0xfd: printf("CALL   $%02x%02x",*(state->memory + state->pc + 2),*(state->memory + state->pc + 1)); 
            
            call(state->pc + 3);
            break;
        
        
        case 0xfe: printf("CPI    #$%02x",*(state->memory + state->pc + 1));state->pc+=2;UnimplementedInstruction(state); break;
        case 0xff: printf("RST 7"); state->pc++;UnimplementedInstruction(state); break;
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

void movM(uint8_t registerToRcv){

    uint16_t offset = ((state->h <<8) | state->l);
    registerToRcv = state->memory[offset];

}

void mov(uint8_t toRcv, uint8_t toTrans){

    toRcv = toTrans;
}

void popPSW(){

    state->a = state->memory[state->sp+1];    
    
    uint8_t psw = state->memory[state->sp];    
    state->cc.zero  = (0x01 == (psw & 0x01));    
    state->cc.sign  = (0x02 == (psw & 0x02));    
    state->cc.parity  = (0x04 == (psw & 0x04));    
    state->cc.carry = (0x08 == (psw & 0x08));    
    state->cc.ac = (0x10 == (psw & 0x10));    
    
    state->sp += 2;

}


void pushPSW(){

    state->memory[state->sp-1] = state->a;    
    uint8_t psw = (state->cc.zero |    
                    state->cc.sign << 1 |    
                    state->cc.parity << 2 |    
                    state->cc.carry << 3 |    
                    state->cc.ac << 4 );    
    state->memory[state->sp-2] = psw;    
    state->sp = state->sp - 2;

}


void push(uint8_t register1,uint8_t register2){ 

    state->memory[state->sp-1] = register1;
    state->memory[state->sp-2] = register2;

    state->sp = state->sp - 2;

}

void pop(uint8_t register1, uint8_t register2){
    register1 = state->memory[state->sp+1];
    register2 = state->memory[state->sp];

    state->sp += 2;

}


void ana(uint8_t register1){
    state->a = ((state->a & register1) & 0xFF); 
}


void call(uint16_t ret){

    state->memory[state->sp-1] = (ret >> 8) & 0xff;
    state->memory[state->sp-2] = ret & 0xff;

    state->sp = state->sp - 2;
    state->pc = (state->memory[state->pc + 2] << 8) | state->memory[state->pc + 1]; 
}

void ret(){
     state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);    
     state->sp += 2;
}


void jnz(uint16_t address){
    
    if (state->cc.zero == 0)
    {
        state->pc = address; 
    }else{
        state->pc += 3;
    }
}


void jmp(uint16_t address){

    state->pc = address;
}



void dad(uint8_t register1, uint8_t register2){

    uint16_t h_l = ((uint16_t)(state->h << 8)) | ((uint16_t)(state->l));
    uint16_t new_val = ((uint16_t)(register1 << 8)) | ((uint16_t)(register2));
    uint32_t result = h_l + new_val;

    state->cc.carry = (result > 0xffff);

    h_l = (result & 0xffff);

    state->h = (uint8_t)((new_val & 0xff00) >> 8);
    state->l = (uint8_t)(new_val & 0xff);

    state->pc++;
}

void dcxInx(uint8_t register1, uint8_t register2,char op){

    uint16_t new_val = ((uint16_t)(register1 << 8)) | ((uint16_t)(register2));

    switch(op){
        case 'i':
            new_val = new_val + 1;
            break;
        case 'd':
            new_val = new_val - 1;
            break;
    }

    register1 = (uint8_t)((new_val & 0xff00) >> 8);
    register2 = (uint8_t)(new_val & 0xff);
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

    uint16_t answer = state->a + toAdd;
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

    dissasemble_8080(state);

    return 0;
}


