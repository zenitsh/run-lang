#ifndef __RL_VCPU_H
#define __RL_VCPU_H
#include "rnvm/rl_util.h"

typedef struct{
    RLint R[32];
    RLfloat F[32];
    RLuint P;
    RLuint T;
}RLvcpu;

#pragma pack(1)

typedef struct{
    RLubyte op;
    RLubyte src;
    RLuint dest;
}RLmtype;

typedef struct{
    RLint imm;
    RLubyte dest;
}RLitype;

typedef struct{
    RLfloat imm;
    RLubyte dest;
}RLftype;

typedef struct{
    RLubyte op;
    RLubyte byte;
    RLubyte src;
    RLubyte dest;
}RLrtype;

typedef union{
    RLmtype m;
    RLrtype r;
    RLitype i;
    RLftype f;
}RLctype;

typedef struct{
    RLubyte opcode;
    RLctype number;
    RLubyte w[8-sizeof(RLubyte)-sizeof(RLctype)];
}RLcode;

#pragma pack()

#endif