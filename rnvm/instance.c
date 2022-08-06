#include "rnvm/rnvm.h"
#include "rnvm/rl_instance.h"
#include "rnvm/rl_util.h"
#include <malloc.h>

RLinstance * rlCreateInstance(RLuint size){
    RLinstance * instance = (RLinstance*)malloc(sizeof(RLinstance));
    instance->size = size;
    instance->mem = (RLubyte*)malloc(sizeof(RLubyte)*size);
    instance->cpu.C = 0;
    instance->cpu.P = 0;
    instance->cpu.B = 0;
    return instance;
}

void rlDeleteInstance(RLinstance* instance){
    free(instance->mem);
    free(instance);
}