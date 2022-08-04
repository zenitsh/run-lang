#ifndef __RL_VCPU_H
#define __RL_VCPU_H
#include "rnvm/rl_util.h"

typedef struct{
    RLint R[32];
    RLfloat F[32];
}RLvcpu;

#pragma pack(1)

typedef struct{
    RLubyte rd;
    RLubyte funct3;
    RLubyte rs1;
    RLubyte rs2;
    RLubyte funct7;
    RLubyte w[2];
}RLrtype;

typedef struct{
    RLubyte rd;
    RLubyte funct3;
    RLubyte rs1;
    RLushort imm;
    RLubyte w[2];
}RLitype;

typedef struct{
    RLubyte imm1;
    RLubyte funct3;
    RLubyte rs1;
    RLubyte rs2;
    RLubyte imm2;
    RLubyte w[2];
}RLbstype;

typedef struct{
    RLubyte rd;
    RLuint imm;
    RLubyte w[2];
}RLutype;

typedef struct{
    RLubyte rd;
    RLubyte imm1;
    RLubyte imm2;
    RLubyte imm3;
    RLubyte imm4;
    RLubyte w[2];
}RLjtype;

typedef struct{
    RLubyte opcode;
    union{
        RLrtype r;
        RLitype i;
        RLbstype bs;
        RLutype u;
        RLjtype j;
    }number;
}RLcode;

#pragma pack()

#endif