#include "rnvm/rl_util.h"
#include "rnvm/rl_instance.h"

#include <string.h>
#include <stdio.h>

void rlSetmi(RLinstance * instance, RLuint mem, RLubyte r){memcpy(&instance->mem[mem], &instance->cpu.R[r], sizeof(RLint));}
void rlGetmi(RLinstance * instance, RLuint mem, RLubyte r){memcpy(&instance->cpu.R[r], &instance->mem[mem], sizeof(RLint));}
void rlSetmf(RLinstance * instance, RLuint mem, RLubyte r){memcpy(&instance->mem[mem], &instance->cpu.F[r], sizeof(RLfloat));}
void rlGetmf(RLinstance * instance, RLuint mem, RLubyte r){memcpy(&instance->cpu.F[r], &instance->mem[mem], sizeof(RLfloat));}

void rlSetiim(RLinstance * instance, RLint imm, RLubyte r){instance->cpu.R[r]=imm;}
void rlSetfim(RLinstance * instance, RLfloat imm, RLubyte r){instance->cpu.F[r]=imm;}

void rlSeti(RLinstance * instance, RLubyte r1, RLubyte r2){instance->cpu.R[r2]=instance->cpu.R[r1];}
void rlSetf(RLinstance * instance, RLubyte r1, RLubyte r2){instance->cpu.F[r2]=instance->cpu.F[r1];}

void rlSetif(RLinstance * instance, RLubyte r1, RLubyte r2){instance->cpu.R[r2]=instance->cpu.F[r1];}
void rlSetfi(RLinstance * instance, RLubyte r1, RLubyte r2){instance->cpu.F[r2]=instance->cpu.R[r1];}

void rlAddsi(RLinstance * instance, RLubyte r){instance->cpu.P+=instance->cpu.R[r];}
void rlAddsim(RLinstance * instance, RLint imm){instance->cpu.P+=imm;}
void rlPushi(RLinstance * instance, RLubyte r){memcpy(&instance->mem[instance->cpu.P], &instance->cpu.R[r], sizeof(RLint));instance->cpu.P+=sizeof(RLint);}
void rlPushf(RLinstance * instance, RLubyte r){memcpy(&instance->mem[instance->cpu.P], &instance->cpu.F[r], sizeof(RLfloat));instance->cpu.P+=sizeof(RLfloat);}
void rlPopi(RLinstance * instance, RLubyte r){instance->cpu.P-=sizeof(RLint);memcpy(&instance->cpu.R[r], &instance->mem[instance->cpu.P], sizeof(RLint));}
void rlPopf(RLinstance * instance, RLubyte r){instance->cpu.P-=sizeof(RLfloat);memcpy(&instance->cpu.F[r], &instance->mem[instance->cpu.P], sizeof(RLfloat));}

//rlSwapi
//rlSwapf

void rlAddi(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3){instance->cpu.R[r3]=instance->cpu.R[r1]+instance->cpu.R[r2];}
//rlSubi
//rlMuli
//rlDivi
//rlRemi
//rlAddf
//rlSubf
//rlMulf
//rlDivf

//rlJumpi
void rlJumpim(RLinstance * instance, RLuint imm){instance->cpu.C=imm;};
//jzii
//jnzii
void rlJziim(RLinstance * instance, RLuint imm){instance->cpu.C=imm;};
void rlJnziim(RLinstance * instance, RLuint imm){instance->cpu.C=imm;};
void rlXim(RLinstance * instance, RLuint imm){
    memcpy(&instance->mem[instance->cpu.P], &instance->cpu.C, sizeof(RLuint));
    memcpy(&instance->mem[instance->cpu.P+sizeof(RLuint)], &instance->cpu.B, sizeof(RLuint));
    instance->cpu.P+=sizeof(RLuint)*2;
    instance->cpu.B=instance->cpu.P;
    instance->cpu.C=imm;
    for(int i=0;i<instance->cpu.P;i+=sizeof(RLint))printf("%d|", *(RLint*)&instance->mem[i]);printf("\n");
}

void rlRetn(RLinstance * instance){
    instance->cpu.P=instance->cpu.B;
    instance->cpu.P-=sizeof(RLuint)*2;
    memcpy(&instance->cpu.C, &instance->mem[instance->cpu.P], sizeof(RLuint));
    memcpy(&instance->cpu.B, &instance->mem[instance->cpu.P+sizeof(RLuint)], sizeof(RLuint));
    for(int i=0;i<instance->cpu.P;i+=sizeof(RLint))printf("%d|", *(RLint*)&instance->mem[i]);printf("\n");
    ++instance->cpu.C;
}

void rlSysi(RLinstance * instance, RLubyte r, RLint imm){
    switch(imm){
        case 0x00:
        printf("%d", instance->cpu.R[r]);
        break;
        case 0x01:
        printf("%f", instance->cpu.F[r]);
        break;
    }
}