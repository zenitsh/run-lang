#ifndef __RL_INSTANCE_H
#define __RL_INSTANCE_H
#include "rnvm/rl_util.h"
#include "rnvm/rl_vcpu.h"

typedef struct{
    RLvcpu cpu;
    RLuint size;
    RLubyte * mem;
}RLinstance;

#endif