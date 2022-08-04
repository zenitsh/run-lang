#ifndef __RL_VCPU_H
#define __RL_VCPU_H
#include "rnvm/rl_util.h"

typedef uint8_t RLcode[8];

typedef struct{
    RLint R[32];
    RLfloat F[32];
}RLvcpu;

typedef struct{
    RLubyte opcode;
    RLubyte rd;
    RLubyte funct3;
    RLubyte rs1;
    RLubyte rs2;
    RLubyte funct7;
}RLrtype;

typedef struct{
    RLubyte opcode;
    RLubyte rd;
    RLubyte funct3;
    RLubyte rs1;
    RLuint imm;
}RLitype;

typedef struct{
    RLubyte opcode;
    RLubyte imm1;
    RLubyte funct3;
    RLubyte rs1;
    RLubyte rs2;
    RLubyte imm2;
}RLbstype;

typedef struct{
    RLubyte opcode;
    RLubyte rd;
    RLulong imm;
}RLutype;

typedef struct{
    RLubyte opcode;
    RLubyte rd;
    RLubyte imm1;
    RLubyte imm2;
    RLubyte imm3;
    RLubyte imm4;
}RLjtype;

#endif