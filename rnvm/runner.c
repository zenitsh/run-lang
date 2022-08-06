#include "rnvm/rl_util.h"
#include "rnvm/rl_instance.h"

#include <string.h>
//#include <stdio.h>

void rlSetmi(RLinstance * instance, RLubyte r, RLuint mem){memcpy(&instance->mem[mem], &instance->cpu.R[r], sizeof(RLint));}
void rlGetmi(RLinstance * instance, RLubyte r, RLuint mem){memcpy(&instance->cpu.R[r], &instance->mem[mem], sizeof(RLint));}
void rlSetmf(RLinstance * instance, RLubyte r, RLuint mem){memcpy(&instance->mem[mem], &instance->cpu.F[r], sizeof(RLfloat));}
void rlGetmf(RLinstance * instance, RLubyte r, RLuint mem){memcpy(&instance->cpu.F[r], &instance->mem[mem], sizeof(RLfloat));}

void rlSetmii(RLinstance * instance, RLubyte r1, RLubyte r2){memcpy(&instance->mem[instance->cpu.R[r2]], &instance->cpu.R[r1], sizeof(RLint));}
void rlGetmii(RLinstance * instance, RLubyte r1, RLubyte r2){memcpy(&instance->cpu.R[r1], &instance->mem[instance->cpu.R[r2]], sizeof(RLint));}
void rlSetmfi(RLinstance * instance, RLubyte r1, RLubyte r2){memcpy(&instance->mem[instance->cpu.R[r2]], &instance->cpu.F[r1], sizeof(RLfloat));}
void rlGetmfi(RLinstance * instance, RLubyte r1, RLubyte r2){memcpy(&instance->cpu.F[r1], &instance->mem[instance->cpu.R[r2]], sizeof(RLfloat));}

void rlSetiim(RLinstance * instance, RLint imm, RLubyte r){instance->cpu.R[r]=imm;}
void rlSetfim(RLinstance * instance, RLfloat imm, RLubyte r){instance->cpu.F[r]=imm;}

void rlSeti(RLinstance * instance, RLubyte r1, RLubyte r2){instance->cpu.R[r2]=instance->cpu.R[r1];}
void rlSetf(RLinstance * instance, RLubyte r1, RLubyte r2){instance->cpu.F[r2]=instance->cpu.F[r1];}

void rlSetif(RLinstance * instance, RLubyte r1, RLubyte r2){instance->cpu.R[r2]=instance->cpu.F[r1];}
void rlSetfi(RLinstance * instance, RLubyte r1, RLubyte r2){instance->cpu.F[r2]=instance->cpu.R[r1];}

void rlAddsi(RLinstance * instance, RLubyte r){instance->cpu.P+=instance->cpu.R[r];}
void rlAddsim(RLinstance * instance, RLint imm){instance->cpu.P+=imm;}
void rlSubsim(RLinstance * instance, RLint imm){instance->cpu.P-=imm;}
void rlGetsi(RLinstance * instance, RLubyte r){instance->cpu.R[r]=instance->cpu.P;}
void rlGetbi(RLinstance * instance, RLubyte r){instance->cpu.R[r]=instance->cpu.B;}

//rlSwapi
//rlSwapf

void rlAddi(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3){instance->cpu.R[r3]=instance->cpu.R[r1]+instance->cpu.R[r2];}
void rlSubi(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3){instance->cpu.R[r3]=instance->cpu.R[r1]-instance->cpu.R[r2];}
void rlMuli(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3){instance->cpu.R[r3]=instance->cpu.R[r1]*instance->cpu.R[r2];}
void rlDivi(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3){instance->cpu.R[r3]=instance->cpu.R[r1]/instance->cpu.R[r2];}
void rlRemi(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3){instance->cpu.R[r3]=instance->cpu.R[r1]%instance->cpu.R[r2];}
void rlAddf(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3){instance->cpu.F[r3]=instance->cpu.F[r1]+instance->cpu.F[r2];}
void rlSubf(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3){instance->cpu.F[r3]=instance->cpu.F[r1]-instance->cpu.F[r2];}
void rlMulf(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3){instance->cpu.F[r3]=instance->cpu.F[r1]*instance->cpu.F[r2];}
void rlDivf(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3){instance->cpu.F[r3]=instance->cpu.F[r1]/instance->cpu.F[r2];}


//rlJumpi
void rlJumpim(RLinstance * instance, RLuint imm){instance->cpu.C=imm;}
//jzii
//jnzii
void rlJziim(RLinstance * instance, RLubyte r, RLuint imm){if(instance->cpu.R[r])++instance->cpu.C;else instance->cpu.C=imm;}
void rlJaiim(RLinstance * instance, RLubyte r, RLuint imm){if(instance->cpu.R[r])instance->cpu.C=imm;else ++instance->cpu.C;}
void rlXim(RLinstance * instance, RLuint imm){
    memcpy(&instance->mem[instance->cpu.P], &instance->cpu.C, sizeof(RLuint));
    memcpy(&instance->mem[instance->cpu.P+sizeof(RLuint)], &instance->cpu.B, sizeof(RLuint));
    instance->cpu.P+=sizeof(RLuint)*2;
    instance->cpu.B=instance->cpu.P;
    instance->cpu.C=imm;
    //for(int i=0;i<instance->cpu.P;i+=sizeof(RLint))printf("%d|", *(RLint*)&instance->mem[i]);printf("\n");
}

void rlRetn(RLinstance * instance){
    instance->cpu.P=instance->cpu.B;
    instance->cpu.P-=sizeof(RLuint)*2;
    memcpy(&instance->cpu.C, &instance->mem[instance->cpu.P], sizeof(RLuint));
    memcpy(&instance->cpu.B, &instance->mem[instance->cpu.P+sizeof(RLuint)], sizeof(RLuint));
    //for(int i=0;i<instance->cpu.P;i+=sizeof(RLint))printf("%d|", *(RLint*)&instance->mem[i]);printf("\n");
}