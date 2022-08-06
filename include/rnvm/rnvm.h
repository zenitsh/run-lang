#ifndef __RNVM_H
#define __RNVM_H

#include "rnvm/rl_util.h"
#include "rnvm/rl_instance.h"

void rlSetmi(RLinstance * instance, RLubyte r, RLuint mem);
void rlGetmi(RLinstance * instance, RLubyte r, RLuint mem);
void rlSetmf(RLinstance * instance, RLubyte r, RLuint mem);
void rlGetmf(RLinstance * instance, RLubyte r, RLuint mem);

void rlSetmii(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlGetmii(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlSetmfi(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlGetmfi(RLinstance * instance, RLubyte r1, RLubyte r2);

void rlSetioi(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlGetioi(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlSetiof(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlGetiof(RLinstance * instance, RLubyte r1, RLubyte r2);

void rlSetiim(RLinstance * instance, RLint imm, RLubyte r);
void rlSetfim(RLinstance * instance, RLfloat imm, RLubyte r);

void rlSeti(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlSetf(RLinstance * instance, RLubyte r1, RLubyte r2);

void rlSetif(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlSetfi(RLinstance * instance, RLubyte r1, RLubyte r2);

void rlAddsi(RLinstance * instance, RLubyte r);
void rlAddsim(RLinstance * instance, RLint imm);
void rlSubsim(RLinstance * instance, RLint imm);
void rlGetsi(RLinstance * instance, RLubyte r);
void rlGetbi(RLinstance * instance, RLubyte r);

//rlSwapi
//rlSwapf

void rlAddi(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3);
void rlSubi(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3);
void rlMuli(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3);
void rlDivi(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3);
void rlRemi(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3);
void rlAddf(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3);
void rlSubf(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3);
void rlMulf(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3);
void rlDivf(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3);

//rlJumpi
void rlJumpim(RLinstance * instance, RLuint imm);
//jzii
//jnzii
void rlJziim(RLinstance * instance, RLubyte r, RLuint imm);
void rlJaiim(RLinstance * instance, RLubyte r, RLuint imm);

void rlXim(RLinstance * instance, RLuint imm);
void rlRetn(RLinstance * instance);
void rlSysi(RLinstance * instance, RLubyte r, RLint imm);

void rlInterpret(RLinstance * instance, const char * code);
RLinstance * rlCreateInstance(RLuint size);
void rlDeleteInstance(RLinstance* instance);

#endif