#include "rnvm/rl_reader.h"
#include "rnvm/rl_util.h"

RLresult rlRead(RLinstance * instance, RLcode code){
    RLubyte opcode;
    opcode = code.opcode;
    switch(opcode){
        case 0x1f:
            break;
        case 0x2f:
            break;
        case 0x3f:
            break;
        case 0x4f:
            break;
    }
    return RL_SUCCESS;
}