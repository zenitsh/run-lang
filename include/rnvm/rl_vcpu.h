#ifndef __RL_VCPU_H
#define __RL_VCPU_H
#include "rnvm/rl_util.h"

typedef struct{
    RLint R[32];
    RLfloat F[32];
    RLuint C;
    RLuint P;
    RLuint B;
}RLvcpu;

#pragma pack(1)

typedef struct{
    RLubyte op;
    RLubyte op2;
    RLubyte src;
    RLuint dest;
}RLmtype;

typedef struct{
    RLint imm;
    RLubyte dest;
    RLubyte w[2];
}RLitype;

typedef struct{
    RLfloat imm;
    RLubyte dest;
    RLubyte w[2];
}RLftype;

typedef struct{
    RLubyte op;
    RLubyte op2;
    RLubyte src1;
    RLubyte src2;
    RLubyte dest;
    RLubyte w[2];
}RLrtype;


typedef union{
    RLubyte p;//push pointer?
    RLubyte c;
    RLuint j;
    RLubyte w[1];
}RLjtype;

typedef union{
    RLmtype m;
    RLrtype r;
    RLitype i;
    RLftype f;
    RLjtype j;
}RLctype;

typedef struct{
    RLubyte opcode;
    RLctype number;
}RLcode;

#pragma pack()

#endif