#include "rnvm/rl_reader.h"
#include "rnvm/rl_util.h"

RLresult rlRead(RLinstance * instance, RLcode code){
    RLubyte opcode;
    RLubyte rd;
    RLubyte rs1;
    RLubyte rs2;
    RLuint imm1;
    RLuint imm2;
    
    opcode = code[0]&RL_BIN(111111);
    switch(opcode){
    }
    return RL_SUCCESS;
}